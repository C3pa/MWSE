#include "LuaReferenceSceneNodeCreatedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Reference.h"

namespace mwse::lua::event {
	ReferenceSceneNodeCreatedEvent::ReferenceSceneNodeCreatedEvent(TES3::Reference* reference) :
		ObjectFilteredEvent("referenceSceneNodeCreated", reference->baseObject),
		m_Reference(reference)
	{

	}

	sol::table ReferenceSceneNodeCreatedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["reference"] = m_Reference;

		return eventData;
	}

	bool ReferenceSceneNodeCreatedEvent::m_EventEnabled = false;
}
