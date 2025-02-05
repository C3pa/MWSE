--- @meta

--- The spellTick event happens every frame that an effect is active on a target. This can be used to aid in scripted spells, cancel active spells, or otherwise monitor spell activity on actors.
--- @class spellTickEventData
--- @field block boolean If set to `true`, vanilla logic will be suppressed. Returning `false` will set this to `true`.
--- @field claim boolean If set to `true`, any lower-priority event callbacks will be skipped. Returning `false` will set this to `true`.
--- @field caster tes3reference *Read-only*. The caster of the spell.
--- @field deltaTime number *Read-only*. The number of seconds since the last spell tick.
--- @field effect tes3magicEffect *Read-only*. The individual effect structure on source.
--- @field effectId number *Read-only*. The magic effect ID that is being ticked.
--- @field effectIndex number *Read-only*. The index of the effect in source’s effects list.
--- @field effectInstance tes3magicEffectInstance *Read-only*. The unique instance of the magic effect.
--- @field source tes3alchemy|tes3enchantment|tes3spell *Read-only*. The magic source.
--- @field sourceInstance tes3magicSourceInstance *Read-only*. The unique instance of the magic source.
--- @field target tes3reference *Read-only*. The target of the spell. For self-targeted spells, this matches caster.
