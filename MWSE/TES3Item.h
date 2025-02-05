#pragma once

#include "TES3Defines.h"

#include "TES3Object.h"

namespace TES3 {
	// Dummy structure we mostly use for Lua casting.
	struct Item : PhysicalObject {
		//
		// Custom functions.
		//

		ItemData * createItemData();
		bool promptsEquipmentReevaluation() const;

	};
	static_assert(sizeof(Item) == 0x30, "TES3::Item failed size validation");
}

MWSE_SOL_CUSTOMIZED_PUSHER_DECLARE_TES3(TES3::Item)
