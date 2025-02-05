#include "LuaButtonPressedEvent.h"

#include "LuaManager.h"

namespace mwse::lua::event {
	ButtonPressedEvent::ButtonPressedEvent(int buttonId) :
		GenericEvent("buttonPressed"),
		m_ButtonId(buttonId)
	{

	}

	sol::table ButtonPressedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["button"] = m_ButtonId;

		return eventData;
	}

	bool ButtonPressedEvent::m_EventEnabled = false;
}
