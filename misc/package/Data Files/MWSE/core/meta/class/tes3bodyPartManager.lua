--- @meta

--- A game object which holds information about body parts.
--- @class tes3bodyPartManager
--- @field activeBodyParts table *Read-only*. The access to the reference's [`tes3bodyPartManagerActiveBodyPart`](https://mwse.github.io/MWSE/types/tes3bodyPartManagerActiveBodyPart/) objects. It's a 2-dimensional table, with first dimension index values from [`tes3.activeBodyPartLayer`](https://mwse.github.io/MWSE/references/active-body-part-layers/) namespace, while its second dimension indexes are values from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @field animationPhase number *Read-only*. 
--- @field attachNodes table *Read-only*. The access to the reference's [`tes3bodyPartManagerAttachNode`](https://mwse.github.io/MWSE/types/tes3bodyPartManagerAttachNode/) objects. Indexes of that table are values from [`tes3.bodyPartAttachment`](https://mwse.github.io/MWSE/references/body-part-attachments/) namespace.
--- @field reference tes3reference *Read-only*. The access to the reference this body part manager operates for.
tes3bodyPartManager = {}

--- The method fetches active body part of a actor at a given layer and position.
--- @param layer number A value from [`tes3.activeBodyPartLayer`](https://mwse.github.io/MWSE/references/active-body-part-layers/) namespace.
--- @param index number A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @return tes3bodyPartManagerActiveBodyPart result No description yet available.
function tes3bodyPartManager:getActiveBodyPart(layer, index) end

--- The method fetches active body part of a actor for the given item.
--- @param item tes3alchemy|tes3apparatus|tes3armor|tes3book|tes3clothing|tes3ingredient|tes3light|tes3lockpick|tes3misc|tes3probe|tes3repairTool|tes3weapon The item to fetch the active body part for.
--- @return tes3bodyPartManagerActiveBodyPart result No description yet available.
function tes3bodyPartManager:getActiveBodyPartForItem(item) end

--- The method fetches the NiNode-derived object for the loaded mesh of an active body part at a given layer and position.
--- @param layer number A value from [`tes3.activeBodyPartLayer`](https://mwse.github.io/MWSE/references/active-body-part-layers/) namespace.
--- @param index number A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @return niBillboardNode|niCollisionSwitch|niNode|niSwitchNode result No description yet available.
function tes3bodyPartManager:getActiveBodyPartNode(layer, index) end

--- The method removes all currently equipped layers from the actor.
function tes3bodyPartManager:removeEquippedLayers() end

--- The method sets a niNode derived object as active body part at a given layer and position.
--- @param layer number A value from [`tes3.activeBodyPartLayer`](https://mwse.github.io/MWSE/references/active-body-part-layers/) namespace.
--- @param index number A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @param overwriteData boolean *Default*: `true`. A flag which controls whether the current data should be overwritten.
--- @param node niBillboardNode|niCollisionSwitch|niNode|niSwitchNode *Default*: `nil`. 
function tes3bodyPartManager:setActivePartData(layer, index, overwriteData, node) end

--- The method sets a new body part for a given object.
--- @param object tes3activator|tes3alchemy|tes3apparatus|tes3armor|tes3bodyPart|tes3book|tes3clothing|tes3container|tes3containerInstance|tes3creature|tes3creatureInstance|tes3door|tes3ingredient|tes3leveledCreature|tes3leveledItem|tes3light|tes3lockpick|tes3misc|tes3npc|tes3npcInstance|tes3probe|tes3repairTool|tes3static|tes3weapon An object whose body part to set.
--- @param index number A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @param bodyPartId string The unique ID of the `tes3bodyPart` object to set as a new body part for given object.
--- @param isFirstPerson boolean *Default*: `false`. A flag which controls whether the body part is used in first person.
function tes3bodyPartManager:setBodyPartByIdForObject(object, index, bodyPartId, isFirstPerson) end

--- The method sets a new body part for a given object.
--- @param object tes3activator|tes3alchemy|tes3apparatus|tes3armor|tes3bodyPart|tes3book|tes3clothing|tes3container|tes3containerInstance|tes3creature|tes3creatureInstance|tes3door|tes3ingredient|tes3leveledCreature|tes3leveledItem|tes3light|tes3lockpick|tes3misc|tes3npc|tes3npcInstance|tes3probe|tes3repairTool|tes3static|tes3weapon An object whose body part to set.
--- @param index number A value from [`tes3.activeBodyPart`](https://mwse.github.io/MWSE/references/active-body-parts/) namespace.
--- @param bodyPart tes3bodyPart The `tes3bodyPart` object to set as a new body part for given object.
--- @param isFirstPerson boolean *Default*: `false`. A flag which controls whether the body part is used in first person.
function tes3bodyPartManager:setBodyPartForObject(object, index, bodyPart, isFirstPerson) end

--- The method updates all body parts for a given reference.
--- @param reference tes3reference The reference whose body parts to update.
function tes3bodyPartManager:updateForReference(reference) end

