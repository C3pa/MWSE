#pragma once

#include "TES3Util.h"

#include "LuaBaseEvent.h"

namespace mwse {
	namespace lua {
		typedef std::unordered_map<unsigned long, sol::object> UserdataMap;

		class TimerController;
		class LuaManager;

		enum class TimerType {
			RealTime,
			SimulationTime,
			GameTime
		};

		class ThreadedStateHandle {
		public:
			ThreadedStateHandle(LuaManager *);
			~ThreadedStateHandle();

			// Trigger a thread-safe event.
			sol::object triggerEvent(event::BaseEvent*);

			sol::state& state;

		private:
			LuaManager * luaManager;
		};

		class LuaManager {
			friend class ThreadedStateHandle;

		public:
			// Returns an instance to the singleton.
			static LuaManager& getInstance() {
				return singleton;
			};

			// Returns a thread-locking reference to the sol2 lua state.
			ThreadedStateHandle getThreadSafeStateHandle();

			const sol::state_view& getReadOnlyStateView();

			// Uses the MemoryUtil library to create the necessary injections into Morrowind.
			void hook();

			// Performs cleanup to safely detach the DLL.
			void cleanup();

			// Set context for lua scripts.
			TES3::Script* getCurrentScript();
			void setCurrentScript(TES3::Script*);
			TES3::Reference* getCurrentReference();
			void setCurrentReference(TES3::Reference*);

			// Handle our button pressed callbacks. There can only be one at a time.
			void setButtonPressedCallback(sol::optional<sol::protected_function>);
			void triggerButtonPressed();

			// Helper function to execute main.lua scripts recursively in a directory.
			void executeMainModScripts(const char* path, const char* filename = "main.lua");

			// Management functions for timers.
			void updateTimers(float deltaTime, double simulationTimestamp, bool simulating);
			void savePersistentTimers();
			void restorePersistentTimers();
			void clearPersistentTimers();
			void clearTimers();
			std::shared_ptr<TimerController> getTimerController(TimerType type);
			TimerType getTimerControllerType(std::shared_ptr<TimerController> controller);

			//
			void claimLuaThread();
			void releaseLuaThread();

			bool overrideScript(const char* scriptId, sol::object function);
			bool clearScriptOverride(const char* scriptId);

			// Lua-bound static functions.
			static void lua_print(sol::object object);


		private:
			LuaManager();

			//
			void bindData();

			// Event management.
			sol::object triggerEvent(event::BaseEvent*);

			// 
			static LuaManager singleton;

			// 
			sol::state luaState;

			std::recursive_mutex stateThreadMutex;

			//
			TES3::Script* currentScript = nullptr;
			TES3::Reference* currentReference = nullptr;

			// Storage for our current button pressed callback.
			sol::protected_function buttonPressedCallback = sol::nil;

		public:
			// Timers.
			std::shared_ptr<TimerController> gameTimers;
			std::shared_ptr<TimerController> simulateTimers;
			std::shared_ptr<TimerController> realTimers;
		};
	}
}
