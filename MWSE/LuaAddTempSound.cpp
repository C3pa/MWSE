#include "LuaAddTempSoundEvent.h"

#include "TES3Sound.h"
#include "TES3Reference.h"

#include "LuaManager.h"
#include "LuaUtil.h"

namespace mwse::lua::event {
	AddTempSoundEvent::AddTempSoundEvent(const char* path, TES3::Reference* reference, int playbackFlags, unsigned char volume, float pitch, bool isVoiceover, TES3::Sound* sound) :
		GenericEvent("addTempSound"),
		m_Path(path),
		m_Reference(reference),
		m_Flags(playbackFlags),
		m_Volume(volume),
		m_Pitch(pitch),
		m_IsVoiceover(isVoiceover),
		m_Sound(sound)
	{

	}

	sol::table AddTempSoundEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["path"] = m_Path;
		eventData["reference"] = makeLuaObject(m_Reference);
		eventData["flags"] = m_Flags;
		eventData["volume"] = m_Volume;
		eventData["pitch"] = m_Pitch;
		eventData["isVoiceover"] = m_IsVoiceover;
		eventData["sound"] = makeLuaObject(m_Sound);

		return eventData;
	}

	sol::object AddTempSoundEvent::getEventOptions() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::table options = stateHandle.state.create_table();
		options["filter"] = m_Sound;
		return options;
	}

	bool AddTempSoundEvent::m_EventEnabled = false;
}
