return {
	type = "event",
    description = "",
    eventData = {
        ["power"] = {
            type = "tes3spell",
            readOnly = true,
            description = "",
        },
        ["mobile"] = {
            type = "tes3mobileActor",
            readOnly = true,
            description = "",
        },
        ["reference"] = {
            type = "tes3reference",
            readOnly = true,
            description = "Mobile’s associated reference.",
        },
    },
    filter = "power",
}
