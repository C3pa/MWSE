--- @meta

--- The **equipmentReevaluated** event fires after an actor has gone through its items and determined if anything in its inventory is better than what it currently has equipped. This event can be used to force equip new, custom equipment slots if needed.
--- @class equipmentReevaluatedEventData
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field actor tes3container|tes3containerInstance|tes3creature|tes3creatureInstance|tes3npc|tes3npcInstance *Read-only*. The actor that has reevaluated their equipment.
--- @field mobile tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. The mobile actor that has reevaluated their equipment.
--- @field reference tes3reference *Read-only*. The reference that has reevaluated their equipment.
