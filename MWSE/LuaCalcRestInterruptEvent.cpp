#include "LuaCalcRestInterruptEvent.h"

#include "LuaManager.h"

#include "TES3MobilePlayer.h"
#include "TES3WorldController.h"

namespace mwse::lua::event {
	CalcRestInterruptEvent::CalcRestInterruptEvent(int count, int hour) :
		GenericEvent("calcRestInterrupt"),
		m_Count(count),
		m_Hour(hour)
	{

	}

	sol::table CalcRestInterruptEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();


		eventData["count"] = m_Count;
		eventData["hour"] = m_Hour;

		// Add easy access to sleeping and waiting state.
		TES3::MobilePlayer* macp = TES3::WorldController::get()->getMobilePlayer();
		eventData["resting"] = macp->sleeping;
		eventData["waiting"] = macp->waiting;

		return eventData;
	}

	bool CalcRestInterruptEvent::m_EventEnabled = false;
}
