--- @meta

--- A structure that keeps track of combat session data.
--- @class tes3combatSession
--- @field alchemyPriority number No description yet available.
--- @field data any No description yet available.
--- @field distance number No description yet available.
--- @field lastUseTimestamp number No description yet available.
--- @field mobile tes3mobileActor|tes3mobileCreature|tes3mobileNPC|tes3mobilePlayer *Read-only*. No description yet available.
--- @field potionUseFlag number No description yet available.
--- @field selectedAction number No description yet available.
--- @field selectedAlchemy tes3alchemy No description yet available.
--- @field selectedItem tes3itemStack No description yet available.
--- @field selectedShield tes3equipmentStack *Read-only*. No description yet available.
--- @field selectedSpell tes3spell No description yet available.
--- @field selectedWeapon tes3equipmentStack *Read-only*. No description yet available.
--- @field selectionPriority number No description yet available.
tes3combatSession = {}

--- This method equips an item to the mobile in this combat sesion.
--- @param equipmentStack tes3equipmentStack An item to equip.
function tes3combatSession:changeEquipment(equipmentStack) end

--- Selects the alchemy item with the greatest value, for a given effect ID and loads it into the `selectedAlchemy` property.
--- @param id number No description yet available.
--- @return number result No description yet available.
function tes3combatSession:selectAlchemyWithEffect(id) end

