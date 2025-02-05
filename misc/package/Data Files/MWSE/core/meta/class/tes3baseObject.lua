--- @meta

--- Almost anything that can be represented in the Construction Set is based on this structure.
--- @class tes3baseObject
--- @field blocked boolean The blocked state of the object.
--- @field deleted boolean *Read-only*. The deleted state of the object.
--- @field disabled boolean *Read-only*. The disabled state of the object.
--- @field id string *Read-only*. The unique identifier for the object.
--- @field modified boolean The modification state of the object since the last save.
--- @field objectFlags number *Read-only*. The raw flags of the object.
--- @field objectType number *Read-only*. The type of object. Maps to values in [`tes3.objectType`](https://mwse.github.io/MWSE/references/object-types/).
--- @field persistent boolean The persistent flag of the object.
--- @field sourceless boolean The soruceless flag of the object.
--- @field sourceMod string *Read-only*. The filename of the mod that owns this object.
--- @field supportsLuaData boolean If true, references of this object can store temporary or persistent lua data.
tes3baseObject = {}

--- Serializes the object to json.
--- @return string string No description yet available.
function tes3baseObject:__tojson() end

