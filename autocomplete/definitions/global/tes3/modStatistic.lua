return {
	type = "function",
	description = [[Modifies a statistic on a given actor. This should be used instead of manually setting values on the game structures, to ensure that events and GUI elements are properly handled. Either skill, attribute, or name must be provided.]],
	arguments = {{
		name = "params",
		type = "table",
		tableParams = {
			{ name = "reference", type = "tes3mobileActor|tes3reference|string" },
			{ name = "name", type = "string", optional = true, description = "A generic name of an attribute to set." },
			{ name = "attribute", type = "number", optional = true, description = "The attribute to set." },
			{ name = "skill", type = "number", optional = true, description = "The skill to set." },
			{ name = "base", type = "number", optional = true, description = "If set, the base value will be modified." },
			{ name = "current", type = "number", optional = true, description = "If set, the current value will be modified." },
			{ name = "value", type = "number", optional = true, description = "If set, both the base and current value will be modified." },
			{ name = "limit", type = "boolean", default = false, description = "If set, the attribute won't rise above 100 or fall below 0." },
			{ name = "limitToBase", type = "boolean", default = false, description = "If set, the attribute's current value won't rise above its base value. Useful for health, magicka, and fatigue." },
		},
	}},
	examples = {
		["decreaseHealth"] = {
			title = "Decrease Health of an Actor",
			description = "In this simple example, the current health of an actor, the player, is decreased by 10. To simulate actual combat damage, you should use tes3mobileActor.applyDamage.",
		},
		["increaseMagicka"] = {
			title = "Restore Magicka without Overflowing",
			description = "Magicka is restored without exceeding the magicka pool using the limitToBase flag.",
		},
	},
}