return {
	type = "method",
	description = [[Unregisters an `event` handler.]],
	arguments = {
		{ name = "eventID", type = "string", description = "The event id." },
	},
	returns = {
		{ name = "wasUnregistered", type = "boolean" },
	},
}