--- @meta

--- The mouseAxis event fires when the mouse is moved, providing deltaX and deltaY values.
--- @class mouseAxisEventData
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field deltaX number *Read-only*. The difference in horizontal mouse position from the previous frame.
--- @field deltaY number *Read-only*. The difference in vertical mouse position from the previous frame.
--- @field isAltDown number *Read-only*. True if alt  is held.
--- @field isControlDown number *Read-only*. True if control is held.
--- @field isSuperDown number *Read-only*. True if super (Windows key) is held.
