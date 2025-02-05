--- @meta

--- A combination of a texture, a filter mode, a clamping mode, and an index to a set of texture coordinates.
--- @class niTexturingPropertyMap
--- @field clampMode niTexturingPropertyClampMode The clamp mode for the Map.
--- @field filterMode niTexturingPropertyFilterMode The filter mode for the Map.
--- @field texCoordSet number The texture coordinate set for the Map.
--- @field texture niTexture The texture for the Map.
niTexturingPropertyMap = {}

--- Creates a new basic or bump map.
--- @param params niTexturingPropertyMap.new.params This table accepts the following values:
--- 
--- `texture`: niTexture — *Optional*. If provided, sets the map texture to the given value.
--- 
--- `clampMode`: number — *Default*: `WRAP_S_WRAP_T`. The clamp mode to set the map to use.
--- 
--- `filterMode`: number — *Default*: `TRILERP`. The filter mode to set the map to use.
--- 
--- `textCoords`: number — *Default*: `0`. The texture coordinates to set the map to use.
--- 
--- `isBumpMap`: boolean — *Default*: `false`. If true, a bump map will be created instead.
--- @return niTexturingPropertyMap map The created basic or bump map.
function niTexturingPropertyMap.new(params) end

---Table parameter definitions for `niTexturingPropertyMap.new`.
--- @class niTexturingPropertyMap.new.params
--- @field texture niTexture *Optional*. If provided, sets the map texture to the given value.
--- @field clampMode number *Default*: `WRAP_S_WRAP_T`. The clamp mode to set the map to use.
--- @field filterMode number *Default*: `TRILERP`. The filter mode to set the map to use.
--- @field textCoords number *Default*: `0`. The texture coordinates to set the map to use.
--- @field isBumpMap boolean *Default*: `false`. If true, a bump map will be created instead.

