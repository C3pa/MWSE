#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"

#include "TES3DataHandler.h"
#include "TES3Spell.h"

namespace mwse {
	class xGetSpellEffectInfo : InstructionInterface_t {
	public:
		xGetSpellEffectInfo();
		virtual float execute(VMExecuteInterface& virtualMachine);
	};

	static xGetSpellEffectInfo xGetSpellEffectInfoInstance;

	xGetSpellEffectInfo::xGetSpellEffectInfo() : mwse::InstructionInterface_t(OpCode::xGetSpellEffectInfo) {}

	float xGetSpellEffectInfo::execute(mwse::VMExecuteInterface& virtualMachine) {
		// Get parameters.
		mwseString& effectId = virtualMachine.getString(Stack::getInstance().popLong());
		short effectIndex = Stack::getInstance().popShort();

		// Return values.
		long effectEnumId = TES3::EffectID::None;
		long rangeType = 0;
		long area = 0;
		long duration = 0;
		long magMin = 0;
		long magMax = 0;

		// Validate effect index.
		if (effectIndex >= 1 && effectIndex <= 8) {
			// Get the desired effect.
			TES3::Spell* spell = TES3::DataHandler::get()->nonDynamicData->resolveObjectByType<TES3::Spell>(effectId, TES3::ObjectType::Spell);
			if (spell) {
				TES3::Effect* effect = &spell->effects[effectIndex - 1];
				// If we found an effect, set the values.
				if (effect && effect->effectID != TES3::EffectID::None) {
					effectEnumId = effect->effectID;
					rangeType = int(effect->rangeType);
					area = effect->radius;
					duration = effect->duration;
					magMin = effect->magnitudeMin;
					magMax = effect->magnitudeMax;
				}
			}
			else {
				if constexpr (DEBUG_MWSCRIPT_FUNCTIONS) {
					mwse::log::getLog() << "xGetSpellEffectInfo: No spell found with id '" << effectId << "'." << std::endl;
				}
			}
		}
		else {
			if constexpr (DEBUG_MWSCRIPT_FUNCTIONS) {
				mwse::log::getLog() << "xGetSpellEffectInfo: Invalid effect index. Value must be between 1 and 8." << std::endl;
			}
		}

		mwse::Stack::getInstance().pushLong(magMax);
		mwse::Stack::getInstance().pushLong(magMin);
		mwse::Stack::getInstance().pushLong(duration);
		mwse::Stack::getInstance().pushLong(area);
		mwse::Stack::getInstance().pushLong(rangeType);
		mwse::Stack::getInstance().pushLong(effectEnumId);

		return 0.0f;
	}
}
