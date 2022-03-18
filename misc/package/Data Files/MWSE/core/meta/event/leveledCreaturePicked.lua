--- @meta

--- This event is called after any leveled creature list is resolved. The event may be filtered by its list, and its pick can be overwritten. While this event allows for customization, the leveled list may be altered directly as well.
--- @class leveledCreaturePickedEventData
--- @field block boolean If set to `true`, vanilla logic will be suppressed. Returning `false` will set this to `true`.
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field cell tes3cell|nil The cell associated with the pick, if any. This may be the `spawner`'s cell, the temporarily created empty cell, or the cell the player's sleep was interrupted in.
--- @field list tes3leveledCreature *Read-only*. The list responsible for creating a pick.
--- @field pick tes3creature|nil The result of the pick by vanilla mechanism. This can be modified to change the result to something else.
--- @field source string The context that the creature is being spawned in. Valid values include: `"reference"` for when spawned from a placed leveled spawn; `"emptyCell"` for when the player is exploring empty, undefined exterior cells; `"sleepInterrupt"` for when a random creature is chosen to attack the player when resting; and `"script"` for otherwise scripted picking.
--- @field spawner tes3reference|nil If spawned from a placed leveled creature reference, this is a handle to the creating reference.
