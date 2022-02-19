--- @meta

--- This event fires when a dialogue info object text is retrieved. That can be when starting a conversation with an NPC, a service was refused to the player, NPC's responses to player persuading them and if the subtitles are enabled, getting the text for the subtitle will also trigger `infoGetText` event.
---
--- [Examples available in online documentation](https://mwse.github.io/MWSE/events/infoGetText).
--- @class infoGetTextEventData
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field info tes3dialogueInfo *Read-only*. The dialogue info object.
--- @field loadOriginalText method Loads the original text for the info from the game files, bypassing this event.
--- @field text string The text to return. This can be modified. Does not contain the original text. If not set, the original text will be used instead.
