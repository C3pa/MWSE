#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"
#include "TES3NPC.h"
#include "TES3Creature.h"
#include "TES3Reference.h"

using namespace mwse;

namespace mwse
{
	class xSetBaseGold : mwse::InstructionInterface_t
	{
	public:
		xSetBaseGold();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static xSetBaseGold xSetBaseGoldInstance;

	xSetBaseGold::xSetBaseGold() : mwse::InstructionInterface_t(OpCode::xSetBaseGold) {}

	void xSetBaseGold::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xSetBaseGold::execute(mwse::VMExecuteInterface &virtualMachine)
	{
		short gold = mwse::Stack::getInstance().popShort();

		// Get reference.
		TES3::Reference* reference = virtualMachine.getReference();
		if (reference == NULL) {
#if _DEBUG
			mwse::log::getLog() << "xSetBaseGold: Called on invalid reference." << std::endl;
#endif
			return 0.0f;
		}

		// Get the gold based on the base record type.
		TES3::BaseObject* baseRecord = reference->baseObject;
		if (baseRecord->objectType == TES3::ObjectType::NPC) {
		TES3::NPCInstance* npc = reinterpret_cast<TES3::NPCInstance*>(baseRecord);
			if (npc->baseNPC) {
				npc->baseNPC->barterGold = gold;
			}
			else {
				mwse::log::getLog() << "xSetBaseGold: Could not get base NPC record for \"" << npc->objectID << "\"" << std::endl;
			}
		}
		else if (baseRecord->objectType == TES3::ObjectType::Creature) {
			TES3::CreatureInstance* creature = reinterpret_cast<TES3::CreatureInstance*>(baseRecord);
			if (creature->baseCreature) {
				creature->baseCreature->barterGold = gold;
			}
			else {
				mwse::log::getLog() << "xSetBaseGold: Could not get base creature record for \"" << creature->objectID << "\"" << std::endl;
			}
		}

		return 0.0f;
	}
}