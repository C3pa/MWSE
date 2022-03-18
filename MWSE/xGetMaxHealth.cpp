#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"
#include "TES3MobileNPC.h"
#include "TES3Reference.h"

namespace mwse {
	class xGetMaxHealth : InstructionInterface_t {
	public:
		xGetMaxHealth();
		virtual float execute(VMExecuteInterface& virtualMachine);
	private:
		const float INVALID_VALUE = -1.0f;
	};

	static xGetMaxHealth xGetMaxHealthInstance;

	xGetMaxHealth::xGetMaxHealth() : mwse::InstructionInterface_t(OpCode::xGetMaxHealth) {}

	float xGetMaxHealth::execute(mwse::VMExecuteInterface& virtualMachine) {
		// Get the associated MACP record.
		TES3::Reference* reference = virtualMachine.getReference();
		auto mobileObject = reference->getAttachedMobileActor();
		if (mobileObject == NULL) {
			if constexpr (DEBUG_MWSCRIPT_FUNCTIONS) {
				mwse::log::getLog() << "xGetMaxHealth: Could not find MACP record for reference." << std::endl;
			}
			mwse::Stack::getInstance().pushFloat(INVALID_VALUE);
			return 0.0f;
		}

		// Push the base value of the statistic.
		mwse::Stack::getInstance().pushFloat(mobileObject->health.base);

		return 0.0f;
	}
}
