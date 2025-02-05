#include "LuaUiObjectTooltipEvent.h"

#include "LuaManager.h"
#include "LuaUtil.h"

#include "TES3ItemData.h"
#include "TES3Reference.h"
#include "TES3UIElement.h"

namespace mwse::lua::event {
	UiObjectTooltipEvent::UiObjectTooltipEvent(TES3::UI::Element* tooltip, TES3::Object* object, TES3::ItemData* itemData, int count) :
		GenericEvent("uiObjectTooltip"),
		m_Tooltip(tooltip),
		m_Object(object),
		m_ItemData(itemData),
		m_Count(count)
	{

	}

	sol::table UiObjectTooltipEvent::createEventTable() {
		auto stateHandle = LuaManager::getInstance().getThreadSafeStateHandle();
		sol::state& state = stateHandle.state;
		sol::table eventData = state.create_table();

		// If the object is a reference, expose its base object and the reference.
		if (m_Object->objectType == TES3::ObjectType::Reference) {
			eventData["object"] = static_cast<TES3::Reference*>(m_Object)->baseObject;
			eventData["reference"] = m_Object;
			eventData["itemData"] = static_cast<TES3::Reference*>(m_Object)->getAttachedItemData();
		}
		// Otherwise just expose the object.
		else {
			eventData["object"] = m_Object;
			eventData["itemData"] = m_ItemData;
		}

		eventData["tooltip"] = m_Tooltip;
		eventData["count"] = m_Count;

		return eventData;
	}

	bool UiObjectTooltipEvent::m_EventEnabled = false;
}
