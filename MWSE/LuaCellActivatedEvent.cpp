#include "LuaCellActivatedEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3Cell.h"

namespace mwse::lua::event {
	CellActivatedEvent::CellActivatedEvent(TES3::Cell* cell) :
		ObjectFilteredEvent("cellActivated", cell),
		m_Cell(cell)
	{

	}

	sol::table CellActivatedEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		eventData["cell"] = m_Cell;

		return eventData;
	}

	bool CellActivatedEvent::m_EventEnabled = false;
}
