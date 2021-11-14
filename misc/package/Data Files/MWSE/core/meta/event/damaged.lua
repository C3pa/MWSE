--- @meta

--- The damaged event triggers after an actor has been damaged.
---
--- [Examples available in online documentation](https://mwse.github.io/MWSE/events/damaged).
--- @class damagedEventData
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field activeMagicEffect tes3magicEffect *Read-only*. tes3magicEffect which caused damage. Can be nil.
--- @field attacker tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. The mobile actor dealing the damage. Can be nil.
--- @field attackerReference tes3reference *Read-only*. The attacker mobile's associated reference. Can be nil.
--- @field damage number *Read-only*. The amount of damage done.
--- @field killingBlow boolean *Read-only*. If true, the damage killed the target.
--- @field magicSourceInstance tes3magicSourceInstance tes3magicSourceInstance of a spell that caused damage. Can be nil.
--- @field mobile tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. The mobile actor that took damage.
--- @field projectile tes3mobileProjectile|tes3mobileSpellProjectile *Read-only*. Projectile that dealt the damage. Can be nil.
--- @field reference tes3reference *Read-only*. The mobile’s associated reference.
--- @field source tes3.damageSource constants *Read-only*. The origin of damage. Values of this variable can be: "script", "fall", "suffocation", "attack", "magic", "shield" or nil. These damage sources are present as tes3.damageSource.* constants, and those should be used instead. See the example. Damage with "shield" source comes from magic shields. Other sources are self-explanatory.
