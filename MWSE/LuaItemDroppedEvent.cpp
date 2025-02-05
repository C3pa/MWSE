#include "LuaItemDroppedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Reference.h"

namespace mwse::lua::event {
	ItemDroppedEvent::ItemDroppedEvent(TES3::Reference* reference) :
		ObjectFilteredEvent("itemDropped", reference->baseObject),
		m_Reference(reference)
	{

	}

	sol::table ItemDroppedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["reference"] = m_Reference;

		return eventData;
	}

	bool ItemDroppedEvent::m_EventEnabled = false;
}
