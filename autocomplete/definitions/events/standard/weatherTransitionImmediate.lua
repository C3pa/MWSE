return {
	type = "event",
	description = [[The **weatherChangedImmediate** event occurs when the currently simulated weather is changed without transition. This can occur when going from an interior to an exterior in a new region, or while resting.

This can interrupt weather transitions, which means the [weatherTransitionFinished](https://mwse.github.io/MWSE/events/weatherTransitionFinished) event will not be triggered.]],
	related = { "weatherCycled", "weatherTransitionFinished", "weatherChangedImmediate", "weatherTransitionStarted", "weatherChangedImmediate" },
	eventData = {
		to = {
			type = "tes3weather",
			description = "The weather object that is the new current weather.",
		},
	},
}