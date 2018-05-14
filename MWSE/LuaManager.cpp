#include "LuaManager.h"

#include "mwOffsets.h"
#include "Log.h"
#include "TES3Util.h"
#include "MemoryUtil.h"
#include "ScriptUtil.h"
#include "UIUtil.h"
#include "MWSEDefs.h"

#include "LuaUnifiedHeader.h"

#include "LuaScript.h"

#include "TES3ActorAnimationData.h"
#include "TES3UIInventoryTile.h"

// Lua binding files. These are split out rather than kept here to help with compile times.
#include "StackLua.h"
#include "ScriptUtilLua.h"
#include "StringUtilLua.h"
#include "TES3UtilLua.h"
#include "TES3ActionDataLua.h"
#include "TES3ActivatorLua.h"
#include "TES3AlchemyLua.h"
#include "TES3ApparatusLua.h"
#include "TES3ArmorLua.h"
#include "TES3BookLua.h"
#include "TES3CellLua.h"
#include "TES3ClassLua.h"
#include "TES3ClothingLua.h"
#include "TES3CollectionsLua.h"
#include "TES3ContainerLua.h"
#include "TES3CreatureLua.h"
#include "TES3DataHandlerLua.h"
#include "TES3DoorLua.h"
#include "TES3EnchantmentLua.h"
#include "TES3FactionLua.h"
#include "TES3GameLua.h"
#include "TES3GameSettingLua.h"
#include "TES3IngredientLua.h"
#include "TES3InventoryLua.h"
#include "TES3LightLua.h"
#include "TES3LockpickLua.h"
#include "TES3MagicEffectLua.h"
#include "TES3MiscLua.h"
#include "TES3MobileCreatureLua.h"
#include "TES3MobileNPCLua.h"
#include "TES3MobilePlayerLua.h"
#include "TES3MobileProjectileLua.h"
#include "TES3MoonLua.h"
#include "TES3NPCLua.h"
#include "TES3ProbeLua.h"
#include "TES3RaceLua.h"
#include "TES3ReferenceLua.h"
#include "TES3ReferenceListLua.h"
#include "TES3RegionLua.h"
#include "TES3RepairToolLua.h"
#include "TES3ScriptLua.h"
#include "TES3SkillLua.h"
#include "TES3SoundLua.h"
#include "TES3SpellLua.h"
#include "TES3StaticLua.h"
#include "TES3StatisticLua.h"
#include "TES3UIBlockLua.h"
#include "TES3VectorsLua.h"
#include "TES3WeaponLua.h"
#include "TES3WeatherControllerLua.h"
#include "TES3WeatherLua.h"
#include "TES3WorldControllerLua.h"

#include <filesystem>

#define TES3_HOOK_RUNSCRIPT_LUACHECK 0x5029A4
#define TES3_HOOK_RUNSCRIPT_LUACHECK_SIZE 0x6
#define TES3_HOOK_RUNSCRIPT_LUACHECK_RETURN (TES3_HOOK_RUNSCRIPT_LUACHECK + TES3_HOOK_RUNSCRIPT_LUACHECK_SIZE)

#define TES3_HOOK_SAVE_REFERENCE 0x4E1C95
#define TES3_HOOK_SAVE_REFERENCE_SIZE 0x6
#define TES3_HOOK_SAVE_REFERENCE_RETURN (TES3_HOOK_SAVE_REFERENCE + TES3_HOOK_SAVE_REFERENCE_SIZE)

#define TES3_HOOK_LOAD_REFERENCE 0x4DE532
#define TES3_HOOK_LOAD_REFERENCE_SIZE 0x5
#define TES3_HOOK_LOAD_REFERENCE_RETURN (TES3_HOOK_LOAD_REFERENCE + TES3_HOOK_LOAD_REFERENCE_SIZE)
#define TES3_HOOK_LOAD_REFERENCE_RETURN_SUCCESS 0x4DE406

#define TES3_HOOK_FINISH_INITIALIZATION 0x4BBC0C
#define TES3_HOOK_FINISH_INITIALIZATION_SIZE 0x5
#define TES3_HOOK_FINISH_INITIALIZATION_RETURN (TES3_HOOK_FINISH_INITIALIZATION + TES3_HOOK_FINISH_INITIALIZATION_SIZE)

#define TES3_HOOK_UI_EVENT 0x58371A
#define TES3_HOOK_UI_EVENT_SIZE 0x5
#define TES3_HOOK_UI_EVENT_RETURN (TES3_HOOK_UI_EVENT + TES3_HOOK_UI_EVENT_SIZE)

#define TES3_load_writeChunk 0x4B6BA0
#define TES3_load_readChunk 0x4B6880

#define TES3_ActorAnimData_attackCheckMeleeHit 0x541530

#define TES3_cellChanged 0x45CEF0

namespace mwse {
	namespace lua {
		// Initialize singleton.
		LuaManager LuaManager::singleton;

		// Fast-access mapping from a TES3::Script* to its associated Lua module.
		static std::unordered_map<unsigned long, sol::table> scriptOverrides;

		// The currently executing overwritten script.
		static LuaScript * currentOverwrittenScript = NULL;

		// We still abort the program if an unprotected lua error happens. Here we at least
		// get it in the log so it can be debugged.
		int panic(lua_State* L) {
			const char* message = lua_tostring(L, -1);
			log::getLog() << (message ? message : "An unexpected error occurred and forced the lua state to call atpanic.") << std::endl;
			return 0;
		}

		// LuaManager constructor. This is private, as a singleton.
		LuaManager::LuaManager() {
			// Open default lua libraries.
			luaState.open_libraries();

			// Override the default atpanic to print to the log.
			luaState.set_panic(panic);

			// Overwrite the default print function to print to the MWSE log.
			luaState["print"] = [](sol::object message) {
				sol::state& state = LuaManager::getInstance().getState();
				std::string result = state["tostring"](message);
				log::getLog() << result << std::endl;
			};

			// Bind our data types.
			bindData();
		}

		void LuaManager::bindData() {
			// Bind our LuaScript type, which is used for holding script contexts.
			luaState.new_usertype<LuaScript>("LuaScript",
				sol::constructors<LuaScript()>(),

				// Implement dynamic object metafunctions.
				sol::meta_function::index, &DynamicLuaObject::dynamic_get,
				sol::meta_function::new_index, &DynamicLuaObject::dynamic_set,
				sol::meta_function::length, [](DynamicLuaObject& d) { return d.entries.size(); },

				// Set up read-only properties.
				"script", sol::readonly(&LuaScript::script),
				"reference", sol::readonly(&LuaScript::reference),
				"context", sol::readonly_property([](LuaScript& self) { return std::shared_ptr<ScriptContext>(new ScriptContext(self.script)); })

				);

			// Create the base of API tables.
			luaState["mwse"] = luaState.create_table();
			luaState["mwscript"] = luaState.create_table();

			luaState["mwse"]["getVersion"] = []() {
				return MWSE_VERSION_INTEGER;
			};

			// We want to take care of this here rather than in an external file so we have access to scriptOverrides.
			luaState["mwse"]["overrideScript"] = [](std::string scriptId, std::string target) {
				TES3::Script* script = tes3::getDataHandler()->nonDynamicData->findScriptByName(scriptId.c_str());
				if (script != NULL) {
					sol::state& state = LuaManager::getInstance().getState();
					sol::object result = state.safe_script_file("./Data Files/MWSE/lua/" + target + ".lua");
					if (result.is<sol::table>()) {
						scriptOverrides[(unsigned long)script] = result;
						script->dataLength = 0;
						return true;
					}
				}

				return false;
			};

			luaState["mwse"]["virtualKeyPressed"] = [](int VK_key) {
				return (GetAsyncKeyState(VK_key) & 0x8000) == 0x8000;
			};

			// Add binding for base objects.
			luaState.new_usertype<TES3::BaseObject>("TES3BaseObject",
				"new", sol::no_constructor,
				"objectType", &TES3::BaseObject::objectType
				);
			luaState.new_usertype<TES3::MobileObject>("TES3MobileObject",
				"new", sol::no_constructor,
				"objectType", &TES3::MobileObject::objectType
				);

			// Bind data types.
			bindTES3ActionData();
			bindTES3Activator();
			bindTES3Alchemy();
			bindTES3Apparatus();
			bindTES3Armor();
			bindTES3Book();
			bindTES3Cell();
			bindTES3Class();
			bindTES3Clothing();
			bindTES3Collections();
			bindTES3Container();
			bindTES3Creature();
			bindTES3DataHandler();
			bindTES3Door();
			bindTES3Enchantment();
			bindTES3Faction();
			bindTES3Game();
			bindTES3GameSetting();
			bindTES3Ingredient();
			bindTES3Inventory();
			bindTES3Light();
			bindTES3Lockpick();
			bindTES3MagicEffect();
			bindTES3Misc();
			bindTES3MobileCreature();
			bindTES3MobileNPC();
			bindTES3MobilePlayer();
			bindTES3MobileProjectile();
			bindTES3Moon();
			bindTES3NPC();
			bindTES3Probe();
			bindTES3Race();
			bindTES3Reference();
			bindTES3ReferenceList();
			bindTES3Region();
			bindTES3RepairTool();
			bindTES3Script();
			bindTES3Skill();
			bindTES3Sound();
			bindTES3Spell();
			bindTES3Static();
			bindTES3Statistic();
			bindTES3UIBlock();
			bindTES3Vectors();
			bindTES3Weapon();
			bindTES3Weather();
			bindTES3WeatherController();
			bindTES3WorldController();
		}

		//
		// Hook: Run script.
		//

		// Determines if a script should be overriden, and executes the module::execute function if so.
		static void _stdcall RunScript(TES3::Script* script) {
			// Determine if we own this script.
			auto searchResult = scriptOverrides.find((unsigned long)script);
			if (searchResult == scriptOverrides.end()) {
				return;
			}

			// Update the LuaManager to reference our current context.
			lua::LuaManager& manager = lua::LuaManager::getInstance();
			manager.setCurrentReference(*reinterpret_cast<TES3::Reference**>(TES3_SCRIPTTARGETREF_IMAGE));
			manager.setCurrentScript(script);

			// Get and run the execute function.
			sol::state& state = manager.getState();
			sol::protected_function execute = searchResult->second["execute"];
			if (execute) {
				auto result = execute();
				if (!result.valid()) {
					sol::error error = result;
					log::getLog() << "Lua error encountered when override of script '" << script->name << "':" << std::endl << error.what() << std::endl;
					mwscript::StopScript(script, script);
				}
			}
			else {
				log::getLog() << "No execute function found for script override of '" << script->name << "'. Script execution stopped." << std::endl;
				mwscript::StopScript(script, script);
			}
		}

		// Hook for HookRunScriptIndirect.
		static DWORD callbackRunScript = TES3_HOOK_RUNSCRIPT_LUACHECK_RETURN;
		static __declspec(naked) void HookRunScript() {
			_asm
			{
				// Save all registers.
				pushad

				// Actually use our hook.
				push ebx
				call RunScript

				// Restore all registers.
				popad

				// Overwritten code.
				mov ecx, dword ptr ds : [TES3_SCRIPTTARGETREF_IMAGE]

				// Resume normal execution.
				jmp callbackRunScript
			}
		}

		//
		// Hook: Load reference.
		//

		static DWORD _stdcall LoadReference(TES3::Reference* reference, DWORD loader, DWORD nextSubrecordTag) {
			if (nextSubrecordTag != 'TAUL') {
				return FALSE;
			}

			// Call original readChunk function.
			char buffer[4096] = {};
			bool success = reinterpret_cast<char*(__thiscall *)(DWORD, char*, DWORD)>(TES3_load_readChunk)(loader, buffer, 0);

			// If we for whatever reason failed to load this chunk, bail.
			if (!success) {
				return FALSE;
			}

			// sol isn't always smart about about forming the string, so make sure that the buffer we use is safe.
			std::string safeBuffer(buffer, strlen(buffer));

			// Get our lua table, and replace it with our new table.
			sol::state& state = LuaManager::getInstance().getState();
			sol::table& table = reference->getLuaTable();
			table = state["json"]["decode"](safeBuffer);

			// We successfully read this subrecord, so our jump location is back at the success location.
			return TRUE;
		}

		static DWORD callbackLoadReferenceMiss = TES3_HOOK_LOAD_REFERENCE_RETURN;
		static DWORD callbackLoadReferenceHit = TES3_HOOK_LOAD_REFERENCE_RETURN_SUCCESS;
		static __declspec(naked) void HookLoadReference() {
			_asm
			{
				// Save the registers.
				pushad

				// Actually use our hook.
				push eax
				push ebx
				push[esp + 0x510 + 0x20 + 0x8 + 0x4] // Current frame + pushad + previous arguments + argument 0
				call LoadReference

				// If we returned false, continue normal execution.
				test eax, eax
				jz HookLoadReferenceContinue

				// Otherwise, jump to our success location.
				popad
				cmp eax, 'MANM'
				jmp callbackLoadReferenceHit

		HookLoadReferenceContinue:
				// Return normal execution instead.
				popad
				cmp eax, 'MANM'
				jmp callbackLoadReferenceMiss
			}
		}

		//
		// Hook: Save reference.
		//

		static void _stdcall SaveReference(TES3::Reference* reference, DWORD loader) {
			// Get the associated table.
			sol::table table = reference->getLuaTable();

			// If it is empty, don't bother saving it.
			if (table.empty()) {
				return;
			}

			// Convert the table to json for storage.
			sol::state& state = LuaManager::getInstance().getState();
			std::string json = state["json"]["encode"](table);

			// Call original writechunk function.
			reinterpret_cast<void*(__thiscall *)(DWORD, DWORD, const char*, DWORD)>(TES3_load_writeChunk)(loader, 'TAUL', json.c_str(), json.length() + 1);
		}

		static DWORD callbackSaveReference = TES3_HOOK_SAVE_REFERENCE_RETURN;
		static __declspec(naked) void HookSaveReference() {
			_asm
			{
				// Save registers.
				pushad

				// Actually use our hook.
				push esi
				push ebp
				call SaveReference

				// Restore registers.
				popad

				// Overwritten code.
				mov eax, [ebp+0x8]
				shr eax, 5

				// Resume normal execution.
				jmp callbackSaveReference
			}
		}

		//
		// Hook: Finished initializing game code.
		//

		static void _stdcall FinishInitialization() {
			LuaManager::getInstance().triggerEvent(new GenericEvent("initialized"));
		}

		static DWORD callbackFinishedInitialization = TES3_HOOK_FINISH_INITIALIZATION_RETURN;
		static __declspec(naked) void HookFinishInitialization() {
			_asm
			{
				// Save the registers.
				pushad

				// Actually use our hook.
				call FinishInitialization

				// Resume normal execution.
				popad
				mov eax, 1
				jmp callbackFinishedInitialization
			}
		}

		//
		// Hook: Enter Frame
		//

		void __fastcall EnterFrame(TES3::WorldController* worldController, DWORD _UNUSED_) {
			// Run the function before raising our event.
			worldController->mainLoopBeforeInput();

			// Send off our enterFrame event always.
			LuaManager& luaManager = LuaManager::getInstance();
			if (tes3::ui::getButtonPressedIndex() != -1) {
				luaManager.triggerButtonPressed();
			}

			//
			luaManager.triggerEvent(new FrameEvent(worldController->deltaTime, worldController->flagMenuMode));

			// If we're not in menu mode, send off the simulate event.
			if (worldController->flagMenuMode == 0) {
				luaManager.triggerEvent(new SimulateEvent(worldController->deltaTime));
			}
		}

		//
		// Hook: On PC Equip
		//

		signed char __cdecl OnPCEquip(TES3::UI::InventoryTile* tile) {
			// Execute event. If the event blocked the call, bail.
			sol::object response = LuaManager::getInstance().triggerEvent(new EquipEvent(NULL, tile->item, tile->itemData));
			if (response != sol::nil && response.is<sol::table>()) {
				sol::table eventData = response;
				if (eventData["block"] == true) {
					// If we want to block it, we need to run some functions to clear the held item back to the inventory.
					TES3::UI::Block* inventoryMenu = tes3::ui::getMenuNode(tes3::ui::getInventoryMenuId());
					inventoryMenu->timingUpdate();
					tes3::ui::inventoryAddTile(1, tile);
					inventoryMenu->performLayout(1);
					tes3::ui::flagPaperDollUpdate();
					tes3::ui::inventoryUpdateIcons();
					return 0;
				}
			}

			// Call the original function.
			return tes3::ui::equipInventoryTile(tile);
		}

		//
		// Hook: On Equipped.
		//

		int __fastcall OnEquipped(TES3::Actor* actor, DWORD _UNUSED_, TES3::BaseObject* item, TES3::ItemData* itemData, TES3::EquipmentStack** out_equipmentStack, TES3::MobileActor* mobileActor) {
			// Call our wrapper for the function so that events are triggered.
			return actor->equipItem(item, itemData, out_equipmentStack, mobileActor);
		}

		//
		// Hook: On Unequipped.
		//

		int __fastcall OnUnequipped(TES3::Actor* actor, DWORD _UNUSED_, TES3::BaseObject* item, char unknown1, TES3::MobileActor* mobileActor, char unknown2, TES3::ItemData* itemData) {
			// Call our wrapper for the function so that events are triggered.
			return actor->unequipItem(item, unknown1, mobileActor, unknown2, itemData);
		}

		//
		// Hook: On Activate
		//

		void __fastcall OnActivate(TES3::Reference* target, DWORD _UNUSED_, TES3::Reference* activator, int something) {
			// Call our wrapper for the function so that events are triggered.
			target->activate(activator, something);
		}

		//
		// Hook: On Save
		//

		signed char __fastcall OnSave(TES3::NonDynamicData* nonDynamicData, DWORD _UNUSED_, const char* fileName, const char* saveName) {
			// Call our wrapper for the function so that events are triggered.
			return nonDynamicData->saveGame(fileName, saveName);
		}

		//
		// Hook: On Load
		//

		signed char __fastcall OnLoad(TES3::NonDynamicData* nonDynamicData, DWORD _UNUSED_, const char* fileName) {
			// Call our wrapper for the function so that events are triggered.
			return nonDynamicData->loadGame(fileName);
		}

		signed char __fastcall OnLoadMainMenu(TES3::NonDynamicData* nonDynamicData, DWORD _UNUSED_, const char* fileName) {
			// Call our wrapper for the function so that events are triggered.
			return nonDynamicData->loadGameMainMenu(fileName);
		}

		//
		// Hook: New Game. Points to the load event.
		//

		void OnNewGame() {
			// Call our load event.
			LuaManager& luaManager = LuaManager::getInstance();
			luaManager.triggerEvent(new LoadGameEvent(NULL, false, true));

			// Call original function.
			reinterpret_cast<void(__stdcall *)()>(0x5FAEA0)();

			// Call our post-load event.
			luaManager.triggerEvent(new LoadedGameEvent(NULL, false, true));
		}

		//
		// Hook: On Cell Change
		//

		DWORD __cdecl OnCellChange(DWORD unk1, DWORD unk2, DWORD unk3, float x, float y, float z, TES3::Cell* cell, signed char unk4) {
			DWORD value = reinterpret_cast<DWORD(__cdecl *)(DWORD, DWORD, DWORD, float, float, float, TES3::Cell*, signed char)>(TES3_cellChanged)(unk1, unk2, unk3, x, y, z, cell, unk4);

			// Send off event.
			if (cell != NULL) {
				LuaManager::getInstance().triggerEvent(new CellChangedEvent(cell, x, y, z));
			}

			return value;
		}

		//
		// Hook: Start Combat
		//

		void __fastcall OnStartCombat(TES3::MobileActor* mobileActor, DWORD _UNUSED_, TES3::MobileActor* target) {
			// Call our wrapper for the function so that events are triggered.
			mobileActor->startCombat(target);
		}

		//
		// Hook: Stop Combat
		//

		void __fastcall OnStopCombat(TES3::MobileActor* mobileActor, DWORD _UNUSED_, bool something) {
			// Call our wrapper for the function so that events are triggered.
			mobileActor->stopCombat(something);
		}

		//
		// Hook: Attack
		//

		void __fastcall OnAttack(TES3::ActorAnimationData* animData) {
			// Call original function.
			reinterpret_cast<void(__thiscall *)(TES3::ActorAnimationData*)>(TES3_ActorAnimData_attackCheckMeleeHit)(animData);

			// Prepare our event data.
			LuaManager::getInstance().triggerEvent(new AttackEvent(animData));
		}

		//
		// Mobile projectile actor collision
		//

		char __fastcall OnMobileProjectileActorCollision(TES3::MobileProjectile* mobileProjectile, DWORD _UNUSED_, int referenceIndex) {
			// Call our wrapper for the function so that events are triggered.
			return mobileProjectile->onActorCollision(referenceIndex);
		}

		//
		// UI event hooking.
		//

		signed char __cdecl OnUIEvent(DWORD function, TES3::UI::Block* parent, DWORD prop, DWORD b, DWORD c, TES3::UI::Block* block) {
			// Execute event. If the event blocked the call, bail.
			mwse::lua::LuaManager& luaManager = mwse::lua::LuaManager::getInstance();
			sol::table eventData = luaManager.triggerEvent(new GenericUiPreEvent(parent, block, prop, b, c));
			if (eventData.valid() && eventData["block"] == true) {
				return 0;
			}

			signed char result = reinterpret_cast<signed char (__cdecl *)(TES3::UI::Block*, DWORD, DWORD, DWORD, TES3::UI::Block*)>(function)(parent, prop, b, c, block);

			luaManager.triggerEvent(new GenericUiPostEvent(parent, block, prop, b, c));

			return result;
		}

		static DWORD callbackUIEvent = TES3_HOOK_UI_EVENT_RETURN;
		static __declspec(naked) void HookUIEvent() {
			_asm
			{
				push edi
				call OnUIEvent
				add esp, 0x18
				jmp callbackUIEvent
			}
		}

		//
		// Hook show rest attempt.
		//

		void __cdecl OnShowRestWaitMenu(signed char allowRest) {
			tes3::ui::showRestWaitMenu(allowRest, false);
		}

		void __cdecl OnShowRestWaitMenuScripted(signed char allowRest) {
			tes3::ui::showRestWaitMenu(allowRest, true);
		}

		void LuaManager::hook() {
			// Execute mwse_init.lua
			sol::protected_function_result result = luaState.do_file("Data Files/MWSE/lua/mwse_init.lua");
			if (!result.valid()) {
				sol::error err = result;
				log::getLog() << "ERROR: Failed to initialize MWSE Lua interface. Error encountered when executing mwse_init.lua:\n" << err.what() << std::endl;
			}

			// Bind libraries.
			bindMWSEStack();
			bindScriptUtil();
			bindStringUtil();
			bindTES3Util();

			// Look through the Data Files/MWSE/lua folder and see if there are any mod_init files.
			std::string path = "Data Files/MWSE/lua/";
			for (auto & p : std::experimental::filesystem::recursive_directory_iterator(path)) {
				if (p.path().filename() == "mod_init.lua") {
					// If a parent directory is marked .disabled, ignore files in it.
					if (p.path().string().find(".disabled\\") != std::string::npos) {
#if _DEBUG
						log::getLog() << "[LuaManager] Skipping mod initializer in disabled directory: " << p.path().string() << std::endl;
#endif
						continue;
					}

					result = luaState.do_file(p.path().string());
					if (!result.valid()) {
						sol::error err = result;
						log::getLog() << "[LuaManager] ERROR: Failed to run mod initialization script:\n" << err.what() << std::endl;
					}
#if _DEBUG
					else {
						log::getLog() << "[LuaManager] Invoked mod initialization script: " << p.path().string() << std::endl;
					}
#endif
				}
			}

			// Hook the RunScript function so we can intercept Lua scripts and invoke Lua code if needed.
			DWORD OldProtect;
			VirtualProtect((DWORD*)TES3_HOOK_RUNSCRIPT_LUACHECK, TES3_HOOK_RUNSCRIPT_LUACHECK_SIZE, PAGE_READWRITE, &OldProtect);
			genJump(TES3_HOOK_RUNSCRIPT_LUACHECK, reinterpret_cast<DWORD>(HookRunScript));
			for (DWORD i = TES3_HOOK_RUNSCRIPT_LUACHECK + 5; i < TES3_HOOK_RUNSCRIPT_LUACHECK_RETURN; i++) genNOP(i);
			VirtualProtect((DWORD*)TES3_HOOK_RUNSCRIPT_LUACHECK, TES3_HOOK_RUNSCRIPT_LUACHECK_SIZE, OldProtect, &OldProtect);

			// Hook the load reference function, so we can fetch attached Lua data.
			VirtualProtect((DWORD*)TES3_HOOK_LOAD_REFERENCE, TES3_HOOK_LOAD_REFERENCE_SIZE, PAGE_READWRITE, &OldProtect);
			genJump(TES3_HOOK_LOAD_REFERENCE, reinterpret_cast<DWORD>(HookLoadReference));
			VirtualProtect((DWORD*)TES3_HOOK_LOAD_REFERENCE, TES3_HOOK_LOAD_REFERENCE_SIZE, OldProtect, &OldProtect);

			// Hook the save reference function, so we can save attached Lua data.
			VirtualProtect((DWORD*)TES3_HOOK_SAVE_REFERENCE, TES3_HOOK_SAVE_REFERENCE_SIZE, PAGE_READWRITE, &OldProtect);
			genJump(TES3_HOOK_SAVE_REFERENCE, reinterpret_cast<DWORD>(HookSaveReference));
			for (DWORD i = TES3_HOOK_SAVE_REFERENCE + 5; i < TES3_HOOK_SAVE_REFERENCE_RETURN; i++) genNOP(i);
			VirtualProtect((DWORD*)TES3_HOOK_SAVE_REFERENCE, TES3_HOOK_SAVE_REFERENCE_SIZE, OldProtect, &OldProtect);

			// Event: initialized. Hook just before we return successfully from where game data is loaded.
			VirtualProtect((DWORD*)TES3_HOOK_FINISH_INITIALIZATION, TES3_HOOK_FINISH_INITIALIZATION_SIZE, PAGE_READWRITE, &OldProtect);
			genJump(TES3_HOOK_FINISH_INITIALIZATION, reinterpret_cast<DWORD>(HookFinishInitialization));
			VirtualProtect((DWORD*)TES3_HOOK_FINISH_INITIALIZATION, TES3_HOOK_FINISH_INITIALIZATION_SIZE, OldProtect, &OldProtect);

			// Event: enterFrame.
			genCallUnprotected(0x41ABB0, reinterpret_cast<DWORD>(EnterFrame));

			// Event: equip.
			genCallUnprotected(0x5CB8E7, reinterpret_cast<DWORD>(OnPCEquip));
			genCallUnprotected(0x5D11D9, reinterpret_cast<DWORD>(OnPCEquip));
			genCallUnprotected(0x60E70F, reinterpret_cast<DWORD>(OnPCEquip));
			genCallUnprotected(0x60E9BE, reinterpret_cast<DWORD>(OnPCEquip));

			// Event: equipped.
			genCallUnprotected(0x49F053, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x4D9C66, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x4D9D90, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x528412, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52C7F5, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52C813, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52C83C, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52CC85, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52CE43, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x52D0B9, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x54DDE8, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5CEEB9, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5CF3DB, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5CF788, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5CF825, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5CF89F, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5D00D6, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5D048E, reinterpret_cast<DWORD>(OnEquipped));
			genCallUnprotected(0x5D1468, reinterpret_cast<DWORD>(OnEquipped));

			// Event: unequipped.
			genCallUnprotected(0x46089D, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x460B0F, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x464D99, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x465732, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495954, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495B32, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495BA8, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495C46, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495DA5, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495ED9, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x495F7B, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x496062, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x4960E7, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x49615E, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x496254, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x4962A7, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x496350, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x496620, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x4966AF, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5150FD, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x525042, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x52518F, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5282F4, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5283C1, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x52C6B9, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x541087, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x54DA4B, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x558472, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5586F6, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x569CFB, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x56A914, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x56AF4D, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5B521D, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5B5A1F, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5D09F0, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5D0B4B, reinterpret_cast<DWORD>(OnUnequipped));
			genCallUnprotected(0x5D0C54, reinterpret_cast<DWORD>(OnUnequipped));

			// Event: activate.
			genCallUnprotected(0x41CCC8, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x507298, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x5364CD, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x551002, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x59051F, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x5ADB6E, reinterpret_cast<DWORD>(OnActivate));
			genCallUnprotected(0x613CC9, reinterpret_cast<DWORD>(OnActivate));

			// Event: save/saved.
			genCallUnprotected(0x41B100, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x476F58, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x5C8EDB, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x610578, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x6106BE, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x6108B8, reinterpret_cast<DWORD>(OnSave));
			genCallUnprotected(0x611B69, reinterpret_cast<DWORD>(OnSave));

			// Event: load/loaded.
			genCallUnprotected(0x41B262, reinterpret_cast<DWORD>(OnLoad));
			genCallUnprotected(0x5DD3C9, reinterpret_cast<DWORD>(OnLoad));
			genCallUnprotected(0x5DD59F, reinterpret_cast<DWORD>(OnLoad));
			genCallUnprotected(0x5FB629, reinterpret_cast<DWORD>(OnLoad));

			// Additional load/loaded event for loading from the main menu.
			genCallUnprotected(0x5DD3B6, reinterpret_cast<DWORD>(OnLoadMainMenu));

			// Additional load/loaded events for new game.
			genCallUnprotected(0x5FCCF4, reinterpret_cast<DWORD>(OnNewGame));
			genCallUnprotected(0x5FCDAA, reinterpret_cast<DWORD>(OnNewGame));

			// Event: Cell Change
			genCallUnprotected(0x45C9A2, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x45D356, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x45D3C4, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x4637B0, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x4C4B4F, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x4C51AE, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x4EA137, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x50497D, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x5062FD, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x568360, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x56A735, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x56B7D2, reinterpret_cast<DWORD>(OnCellChange));
			genCallUnprotected(0x619BBF, reinterpret_cast<DWORD>(OnCellChange));

			// Event: Start Combat
			genCallUnprotected(0x5073BC, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x52FC2F, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x530443, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x5563F5, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x5564C2, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x558FE7, reinterpret_cast<DWORD>(OnStartCombat));
			genCallUnprotected(0x55905E, reinterpret_cast<DWORD>(OnStartCombat));

			// Event: Stop Combat
			genCallUnprotected(0x523BBF, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x54E04D, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x556524, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x556568, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x557CBC, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x55916F, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x559265, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x5650F2, reinterpret_cast<DWORD>(OnStopCombat));
			genCallUnprotected(0x568794, reinterpret_cast<DWORD>(OnStopCombat));
			genJumpUnprotected(0x7365E9, reinterpret_cast<DWORD>(OnStopCombat));

			// Event: Melee Hit Check
			genCallUnprotected(0x541489, reinterpret_cast<DWORD>(OnAttack));
			genCallUnprotected(0x5414CD, reinterpret_cast<DWORD>(OnAttack));
			genCallUnprotected(0x569E78, reinterpret_cast<DWORD>(OnAttack));

			// Override the MobileProjectile::onActorCollision vtable for a hit event.
			overrideVirtualTable(0x74B2B4, 0x80, reinterpret_cast<DWORD>(OnMobileProjectileActorCollision));

			// Event: UI Event
			VirtualProtect((DWORD*)TES3_HOOK_UI_EVENT, TES3_HOOK_UI_EVENT_SIZE, PAGE_READWRITE, &OldProtect);
			genJump(TES3_HOOK_UI_EVENT, reinterpret_cast<DWORD>(HookUIEvent));
			for (DWORD i = TES3_HOOK_UI_EVENT + 5; i < TES3_HOOK_UI_EVENT_RETURN; i++) genNOP(i);
			VirtualProtect((DWORD*)TES3_HOOK_UI_EVENT, TES3_HOOK_UI_EVENT_SIZE, OldProtect, &OldProtect);

			// Event: Show Rest/Wait Menu
			genCallUnprotected(0x41ADB6, reinterpret_cast<DWORD>(OnShowRestWaitMenu));
			genCallUnprotected(0x5097BA, reinterpret_cast<DWORD>(OnShowRestWaitMenuScripted));
			genCallUnprotected(0x5097DD, reinterpret_cast<DWORD>(OnShowRestWaitMenuScripted));

			// Make magic effects writable.
			VirtualProtect((DWORD*)TES3_DATA_EFFECT_FLAGS, 4 * 143, PAGE_READWRITE, &OldProtect);
		}

		void LuaManager::cleanup() {
			// Clean up our handles to our override tables. Helps to prevent a crash when
			// closing mid-execution.
			scriptOverrides.clear();
		}

		TES3::Script* LuaManager::getCurrentScript() {
			return currentScript;
		}

		void LuaManager::setCurrentScript(TES3::Script* script) {
			currentScript = script;
		}

		TES3::Reference* LuaManager::getCurrentReference() {
			return currentReference;
		}

		void LuaManager::setCurrentReference(TES3::Reference* reference) {
			currentReference = reference;
		}

		sol::object LuaManager::triggerEvent(BaseEvent* baseEvent) {
			DWORD threadId = GetCurrentThreadId();
			TES3::DataHandler* dataHandler = tes3::getDataHandler();

			// If we're on the main thread, immediately execute the event
			if (threadId == dataHandler->mainThreadID) {
				// Use this opportunity to check for background events that need to run.
				triggerBackgroundThreadEvents();

				// Execute the original event.
				sol::object response = event::trigger(baseEvent->getEventName(), baseEvent->createEventTable());
				delete baseEvent;
				return response;
			}

			// If we're not on the main thread, queue the event to run once we are.
			else if (threadId == dataHandler->backgroundThreadID) {
				backgroundThreadEventsMutex.lock();
				backgroundThreadEvents.push(baseEvent);
				backgroundThreadEventsMutex.unlock();
			}

			// If we're not on the main thread or the background thread we don't know WTF is going on.
			else {
				throw new std::exception("Event triggered from unknown thread!");
			}

			return sol::nil;
		}

		void LuaManager::triggerBackgroundThreadEvents() {
			backgroundThreadEventsMutex.lock();

			while (backgroundThreadEvents.size() > 0) {
				// Pop the event off the stack.
				BaseEvent* baseEvent = backgroundThreadEvents.front();
				backgroundThreadEvents.pop();

				// Trigger it.
				event::trigger(baseEvent->getEventName(), baseEvent->createEventTable());
				delete baseEvent;
			}

			backgroundThreadEventsMutex.unlock();
		}

		void LuaManager::setButtonPressedCallback(sol::optional<sol::protected_function> callback) {
			buttonPressedCallback = callback.value_or(sol::nil);
		}

		sol::object LuaManager::triggerButtonPressed() {
			if (buttonPressedCallback != sol::nil) {
				sol::protected_function callback = buttonPressedCallback;
				buttonPressedCallback = sol::nil;
				sol::table eventData = luaState.create_table();
				eventData["button"] = tes3::ui::getButtonPressedIndex();
				tes3::ui::resetButtonPressedIndex();
				return callback(eventData);
			}

			return sol::nil;
		}
	}
}