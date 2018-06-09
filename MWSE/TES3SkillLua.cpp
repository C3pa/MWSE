#include "TES3SkillLua.h"

#include "sol.hpp"
#include "LuaManager.h"

#include "TES3Skill.h"

namespace mwse {
	namespace lua {
		void bindTES3Skill() {
			// Get our lua state.
			sol::state& state = LuaManager::getInstance().getState();

			// Start our usertype. We must finish this with state.set_usertype.
			auto usertypeDefinition = state.create_simple_usertype<TES3::Skill>();
			usertypeDefinition.set("new", sol::no_constructor);

			// Define inheritance structures. These must be defined in order from top to bottom. The complete chain must be defined.
			usertypeDefinition.set(sol::base_classes, sol::bases<TES3::BaseObject>());

			// Basic property binding.
			usertypeDefinition.set("id", sol::readonly_property(&TES3::Skill::skill));
			usertypeDefinition.set("attribute", &TES3::Skill::governingAttribute);
			usertypeDefinition.set("specialization", &TES3::Skill::specialization);

			// Indirect bindings to unions and arrays.
			usertypeDefinition.set("actions", sol::readonly_property([](TES3::Skill& self) { return std::ref(self.progressActions); }));

			// Finish up our usertype.
			state.set_usertype("tes3skill", usertypeDefinition);
		}
	}
}
