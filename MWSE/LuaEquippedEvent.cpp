#include "LuaEquippedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Actor.h"
#include "TES3ItemData.h"
#include "TES3MobileActor.h"
#include "TES3Reference.h"

namespace mwse::lua::event {
	EquippedEvent::EquippedEvent(TES3::Actor* a, TES3::MobileActor* ma, TES3::BaseObject* i, TES3::ItemData* id) :
		ObjectFilteredEvent("equipped", i),
		m_Actor(a),
		m_MobileActor(ma),
		m_Item(i),
		m_ItemData(id)
	{

	}

	sol::table EquippedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["actor"] = m_Actor;
		eventData["mobile"] = m_MobileActor;
		if (m_MobileActor) {
			eventData["reference"] = m_MobileActor->reference;
		}
		eventData["item"] = m_Item;
		eventData["itemData"] = m_ItemData;

		return eventData;
	}

	bool EquippedEvent::m_EventEnabled = false;
}
