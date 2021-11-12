--- @meta

--- This event is invoked whenever an actor is checking if they can detect another actor sneaking.
--- @class detectSneakEventData
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field detector tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. The mobile actor that is doing the detecting.
--- @field isDetected boolean The previous detection calculated, starting with the base engine result.
--- @field target tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. The mobile actor that is possibly being detected.
