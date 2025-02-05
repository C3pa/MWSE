# mwscript

!!! warning
	This API is deprecated. See below for more information about what to use instead.

The mwscript library allows vanilla mwscript functions to be called. This is not always ideal, and this library is deprecated. Avoid using it if at all possible.

## Functions

### `mwscript.activate`

Use [`tes3reference:activate()`](https://mwse.github.io/MWSE/types/tes3reference/#activate) or [`tes3.setAIActivate()`](https://mwse.github.io/MWSE/apis/tes3/#tes3setaiactivate) instead. Wrapper for the `Activate` mwscript function.

```lua
mwscript.activate({ reference = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.

***

### `mwscript.addItem`

Use [`tes3.addItem()`](https://mwse.github.io/MWSE/apis/tes3/#tes3additem), [`tes3inventory:addItem()`](https://mwse.github.io/MWSE/types/tes3inventory/#additem), or depending on your needs [`tes3mobileActor:equip()`](https://mwse.github.io/MWSE/types/tes3mobileActor/#equip) instead. Wrapper for the `AddItem` mwscript function.

```lua
local executed = mwscript.addItem({ reference = ..., item = ..., count = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string): The item to be added.
	* `count` (number): *Default*: `1`. The number of items to be added.

**Returns**:

* `executed` (boolean)

***

### `mwscript.addSoulGem`

use [`tes3.addItem()`](https://mwse.github.io/MWSE/apis/tes3/#tes3additem) with the `soul` parameter instead. Wrapper for the `AddSoulGem` mwscript function.

```lua
local executed = mwscript.addSoulGem({ reference = ..., creature = ..., soulgem = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `creature` ([tes3creature](../../types/tes3creature), string): The creature to be stored in the soul gem.
	* `soulgem` ([tes3misc](../../types/tes3misc), string): The soul gem to store the soul in.

**Returns**:

* `executed` (boolean)

***

### `mwscript.addSpell`

Use [`tes3.addSpell()`](https://mwse.github.io/MWSE/apis/tes3/#tes3addspell) or [`tes3spellList:add()`](https://mwse.github.io/MWSE/types/tes3spellList/#add) instead. Wrapper for the `AddSpell` mwscript function.

```lua
local executed = mwscript.addSpell({ reference = ..., spell = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `spell` ([tes3spell](../../types/tes3spell), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.addToLevCreature`

Use [`tes3leveledCreature:insert()`](https://mwse.github.io/MWSE/types/tes3leveledCreature/#insert) instead. Wrapper for the `AddToLevCreature` mwscript function.

```lua
local executed = mwscript.addToLevCreature({ list = ..., creature = ..., level = ... })
```

**Parameters**:

* `params` (table)
	* `list` ([tes3leveledCreature](../../types/tes3leveledCreature), string): Leveled creature list to add a creature to.
	* `creature` ([tes3actor](../../types/tes3actor), string): Creature to add to the list.
	* `level` (number): *Default*: `0`. Minimum level for the creature to spawn.

**Returns**:

* `executed` (boolean)

***

### `mwscript.addToLevItem`

Use [`tes3leveledItem:insert()`](https://mwse.github.io/MWSE/types/tes3leveledItem/#insert) instead. Wrapper for the `AddToLevItem` mwscript function.

```lua
local executed = mwscript.addToLevItem({ list = ..., item = ..., level = ... })
```

**Parameters**:

* `params` (table)
	* `list` ([tes3leveledItem](../../types/tes3leveledItem), string): Leveled item list to add a creature to.
	* `item` ([tes3item](../../types/tes3item), string): Item to add to the list.
	* `level` (number): *Default*: `0`. Minimum level for the item to spawn.

**Returns**:

* `executed` (boolean)

***

### `mwscript.addTopic`

Wrapper for the `AddTopic` mwscript function.

```lua
local executed = mwscript.addTopic({ topic = ... })
```

**Parameters**:

* `params` (table)
	* `topic` ([tes3dialogue](../../types/tes3dialogue), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.aiTravel`

Use [`tes3.setAITravel()`](https://mwse.github.io/MWSE/apis/tes3/#tes3setaitravel) instead. Wrapper for the `AITravel` mwscript function.

```lua
local executed = mwscript.aiTravel({ reference = ..., x = ..., y = ..., z = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `x` (number)
	* `y` (number)
	* `z` (number)

**Returns**:

* `executed` (boolean)

***

### `mwscript.disable`

Use [`tes3reference:disable()`](https://mwse.github.io/MWSE/types/tes3reference/#disable) or [`tes3.setEnabled()`](https://mwse.github.io/MWSE/apis/tes3/#tes3setenabled) instead. Wrapper for the `Disable` mwscript function.

```lua
local executed = mwscript.disable({ reference = ..., modify = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `modify` (boolean): *Default*: `true`. Set the object as modified.

**Returns**:

* `executed` (boolean)

***

### `mwscript.drop`

Use [`tes3.dropItem()`](https://mwse.github.io/MWSE/apis/tes3/#tes3dropitem) or [`tes3inventory:dropItem()`](https://mwse.github.io/MWSE/types/tes3inventory/#dropitem) instead. Wrapper for the `Drop` mwscript function.

```lua
local executed = mwscript.drop({ reference = ..., item = ..., count = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string): The item to be dropped.
	* `count` (number): *Default*: `1`. The number of items to drop.

**Returns**:

* `executed` (boolean)

***

### `mwscript.enable`

Use [`tes3.setEnabled()`](https://mwse.github.io/MWSE/apis/tes3/#tes3setenabled) or [`tes3reference:enable()`](https://mwse.github.io/MWSE/types/tes3reference/#enable) instead. Wrapper for the `Enable` mwscript function.

```lua
local executed = mwscript.enable({ reference = ..., modify = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `modify` (boolean): *Default*: `true`. Set the object as modified.

**Returns**:

* `executed` (boolean)

***

### `mwscript.equip`

Use [`tes3mobileActor:equip()`](https://mwse.github.io/MWSE/types/tes3mobileActor/#equip) or [`tes3mobileActor.combatSession:changeEquipment()`](https://mwse.github.io/MWSE/types/tes3combatSession/#changeequipment) instead. Wrapper for the `Equip` mwscript function.

```lua
local executed = mwscript.equip({ reference = ..., item = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string): The item to be equipped.

**Returns**:

* `executed` (boolean)

***

### `mwscript.explodeSpell`

Use [`tes3.cast()`](https://mwse.github.io/MWSE/apis/tes3/#tes3cast) instead. Wrapper for the `ExplodeSpell` mwscript function.

```lua
local executed = mwscript.explodeSpell({ reference = ..., spell = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `spell` ([tes3spell](../../types/tes3spell), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.getButtonPressed`

Use [`tes3.messageBox()`](https://mwse.github.io/MWSE/apis/tes3/#tes3messagebox) instead. Wrapper for the `GetButtonPressed` mwscript function.

```lua
local buttonIndex = mwscript.getButtonPressed()
```

**Returns**:

* `buttonIndex` (number)

***

### `mwscript.getDetected`

Use [`tes3mobileActor.isPlayerDetected`](https://mwse.github.io/MWSE/types/tes3mobileActor/#isplayerdetected) or depending on what you are doing, [`detectSneak`](https://mwse.github.io/MWSE/events/detectSneak/) event may be desirable. Wrapper for the `GetDetected` mwscript function.

```lua
local result = mwscript.getDetected({ reference = ..., target = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `target` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): Actor to check detection for.

**Returns**:

* `result` (boolean)

***

### `mwscript.getDisabled`

Use [`object.disabled`](https://mwse.github.io/MWSE/types/tes3baseObject/#disabled) on any object inheriting from `tes3baseObject`. Wrapper for the `GetDisabled` mwscript function.

```lua
local result = mwscript.getDisabled({ reference = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.

**Returns**:

* `result` (boolean)

***

### `mwscript.getDistance`

Use [`tes3reference.position`](https://mwse.github.io/MWSE/types/tes3reference/#position) or [`tes3mobileActor.position`](https://mwse.github.io/MWSE/types/tes3mobileActor/#position) to compute the distance or depending on the desired effect, [`tes3mobileActor.playerDistance`](https://mwse.github.io/MWSE/types/tes3mobileActor/#playerdistance). Wrapper for the `GetDistance` mwscript function.

```lua
local result = mwscript.getDistance({ reference = ..., target = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `target` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): Actor to check distance to.

**Returns**:

* `result` (boolean)

***

### `mwscript.getItemCount`

Use [`tes3.getItemCount()`](https://mwse.github.io/MWSE/apis/tes3/#tes3getitemcount) instead. Wrapper for the `GetItemCount` mwscript function.

```lua
local result = mwscript.getItemCount({ reference = ..., item = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string)

**Returns**:

* `result` (number)

***

### `mwscript.getPCJumping`

Use [`tes3.mobilePlayer.isJumping`](https://mwse.github.io/MWSE/types/tes3mobilePlayer/#isjumping) instead. Wrapper for the `GetPCJumping` mwscript function.

```lua
local result = mwscript.getPCJumping()
```

**Returns**:

* `result` (boolean)

***

### `mwscript.getPCRunning`

Use [`tes3.mobilePlayer.isRunning`](https://mwse.github.io/MWSE/types/tes3mobilePlayer/#isrunning) instead. Wrapper for the `GetPCRunning` mwscript function.

```lua
local result = mwscript.getPCRunning()
```

**Returns**:

* `result` (boolean)

***

### `mwscript.getPCSneaking`

Use [`tes3.mobilePlayer.isSneaking`](https://mwse.github.io/MWSE/types/tes3mobilePlayer/#issneaking) instead. Wrapper for the `GetPCSneaking` mwscript function.

```lua
local result = mwscript.getPCSneaking()
```

**Returns**:

* `result` (boolean)

***

### `mwscript.getReference`

Use [`tes3globalScript.reference`](https://mwse.github.io/MWSE/types/tes3globalScript/#reference) instead. Returns the script target for the currently running Morrowind script, if any.

```lua
local result = mwscript.getReference()
```

**Returns**:

* `result` ([tes3reference](../../types/tes3reference))

***

### `mwscript.getScript`

Returns the currently running Morrowind script, if any.

```lua
local result = mwscript.getScript()
```

**Returns**:

* `result` ([tes3script](../../types/tes3script))

***

### `mwscript.getSpellEffects`

Use  [`tes3.isAffectedBy()`](https://mwse.github.io/MWSE/apis/tes3/#tes3isaffectedby) or [`tes3mobileActor:isAffectedByObject()`](https://mwse.github.io/MWSE/types/tes3mobileActor/#isaffectedbyobject) instead. Wrapper for the `GetSpellEffects` mwscript function.

```lua
local result = mwscript.getSpellEffects({ reference = ..., spell = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `spell` ([tes3spell](../../types/tes3spell), string)

**Returns**:

* `result` (boolean)

***

### `mwscript.hasItemEquipped`

Use [`tes3actor:hasItemEquipped()`](https://mwse.github.io/MWSE/types/tes3actor/#hasitemequipped) or [`tes3.getEquippedItem()`](https://mwse.github.io/MWSE/apis/tes3/#tes3getequippeditem) instead. Wrapper for the `HasItemEquipped` mwscript function.

```lua
local result = mwscript.hasItemEquipped({ reference = ..., item = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string): The item to check for.

**Returns**:

* `result` (boolean)

***

### `mwscript.placeAtPC`

Use [`tes3.createReference()`](https://mwse.github.io/MWSE/apis/tes3/#tes3createreference) instead. Wrapper for the `PlaceAtPC` mwscript function.

```lua
local lastPlacedReference = mwscript.placeAtPC({ reference = ..., object = ..., count = ..., distance = ..., direction = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `object` ([tes3object](../../types/tes3object), string): The object to place.
	* `count` (number): *Default*: `1`.
	* `distance` (number): *Default*: `256`.
	* `direction` (number): *Default*: `1`.

**Returns**:

* `lastPlacedReference` ([tes3reference](../../types/tes3reference))

***

### `mwscript.playSound`

Use [`tes3.playSound()`](https://mwse.github.io/MWSE/apis/tes3/#tes3playsound), [`tes3sound:play()`](https://mwse.github.io/MWSE/types/tes3sound/#play) method, or [`tes3.playItemPickupSound()`](https://mwse.github.io/MWSE/apis/tes3/#tes3playitempickupsound) instead. Wrapper for the `PlaySound` mwscript function.

```lua
local result = mwscript.playSound({ reference = ..., sound = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `sound` ([tes3sound](../../types/tes3sound), string)

**Returns**:

* `result` (boolean)

***

### `mwscript.position`

Set [`tes3reference.position`](https://mwse.github.io/MWSE/types/tes3reference/#position) or [`tes3mobileActor.position`](https://mwse.github.io/MWSE/types/tes3mobileActor/#position) to desired new position instead, or use [`tes3.positionCell()`](https://mwse.github.io/MWSE/apis/tes3/#tes3positioncell). Wrapper for the `Position` mwscript function.

```lua
local executed = mwscript.position({ reference = ..., cell = ..., x = ..., y = ..., z = ..., rotation = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `cell` (string)
	* `x` (number): *Default*: `0`.
	* `y` (number): *Default*: `0`.
	* `z` (number): *Default*: `0`.
	* `rotation` (number): *Default*: `0`.

**Returns**:

* `executed` (boolean)

***

### `mwscript.positionCell`

Use [`tes3.positionCell()`](https://mwse.github.io/MWSE/apis/tes3/#tes3positioncell) instead. Wrapper for the `PositionCell` mwscript function.

```lua
local executed = mwscript.positionCell({ reference = ..., cell = ..., x = ..., y = ..., z = ..., rotation = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `cell` (string)
	* `x` (number): *Default*: `0`.
	* `y` (number): *Default*: `0`.
	* `z` (number): *Default*: `0`.
	* `rotation` (number): *Default*: `0`.

**Returns**:

* `executed` (boolean)

***

### `mwscript.removeItem`

Use [`tes3.removeItem()`](https://mwse.github.io/MWSE/apis/tes3/#tes3removeitem), [`tes3.removeItemData()`](https://mwse.github.io/MWSE/apis/tes3/#tes3removeitemdata) or [`tes3inventory:removeItem()`](https://mwse.github.io/MWSE/types/tes3inventory/#removeitem) instead. Wrapper for the `RemoveItem` mwscript function.

```lua
local executed = mwscript.removeItem({ reference = ..., item = ..., count = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `item` ([tes3item](../../types/tes3item), string): The item to be added.
	* `count` (number): *Default*: `1`. The number of items to be added.

**Returns**:

* `executed` (boolean)

***

### `mwscript.removeSpell`

Use [`tes3.removeSpell()`](https://mwse.github.io/MWSE/apis/tes3/#tes3removespell) or [`tes3spellList:remove()`](https://mwse.github.io/MWSE/types/tes3spellList/#remove) instead. Wrapper for the `RemoveSpell` mwscript function.

```lua
local executed = mwscript.removeSpell({ reference = ..., spell = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `spell` ([tes3spell](../../types/tes3spell), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.scriptRunning`

Wrapper for the `ScriptRunning` mwscript function.

```lua
local result = mwscript.scriptRunning({ script = ... })
```

**Parameters**:

* `params` (table)
	* `script` ([tes3script](../../types/tes3script), string)

**Returns**:

* `result` (boolean)

***

### `mwscript.setLevel`

Use [`tes3npc.level`](https://mwse.github.io/MWSE/types/tes3npc/#level) instead. Wrapper for the `SetLevel` mwscript function.

```lua
local executed = mwscript.setLevel({ reference = ..., level = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `level` (number)

**Returns**:

* `executed` (boolean)

***

### `mwscript.startCombat`

Use [`tes3mobileActor:startCombat()`](https://mwse.github.io/MWSE/types/tes3mobileActor/#startcombat) instead. Wrapper for the `StartCombat` mwscript function.

```lua
local executed = mwscript.startCombat({ reference = ..., target = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `target` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): Actor to start combat with.

**Returns**:

* `executed` (boolean)

***

### `mwscript.startScript`

Use [`tes3.runLegacyScript()`](https://mwse.github.io/MWSE/apis/tes3/?h=script#tes3runlegacyscript) instead. Wrapper for the `StartCombat` mwscript function.

```lua
local executed = mwscript.startScript({ reference = ..., script = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `script` ([tes3script](../../types/tes3script), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.stopCombat`

Use [`tes3mobileActor:stopCombat()`](https://mwse.github.io/MWSE/types/tes3mobileActor/#stopcombat) instead. Wrapper for the `StopCombat` mwscript function.

```lua
local executed = mwscript.stopCombat({ reference = ..., target = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `target` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): Actor to stop combat with.

**Returns**:

* `executed` (boolean)

***

### `mwscript.stopScript`

Wrapper for the `StopCombat` mwscript function.

```lua
local executed = mwscript.stopScript({ reference = ..., script = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `script` ([tes3script](../../types/tes3script), string)

**Returns**:

* `executed` (boolean)

***

### `mwscript.stopSound`

Use [`tes3.removeSound()`](https://mwse.github.io/MWSE/apis/tes3/#tes3removesound) or [`tes3sound:stop()`](https://mwse.github.io/MWSE/types/tes3sound/#stop) instead. Wrapper for the `StopSound` mwscript function.

```lua
local result = mwscript.stopSound({ reference = ..., sound = ... })
```

**Parameters**:

* `params` (table)
	* `reference` ([tes3reference](../../types/tes3reference), [tes3mobileActor](../../types/tes3mobileActor), string): *Optional*. The target reference for this command to be executed on. Defaults to the normal script execution reference.
	* `sound` ([tes3sound](../../types/tes3sound), string)

**Returns**:

* `result` (boolean)

***

### `mwscript.wakeUpPC`

Use [`tes3.wakeUp()`](https://mwse.github.io/MWSE/apis/tes3/#tes3wakeup) instead. Wrapper for the `WakeUpPC` mwscript function.

```lua
mwscript.wakeUpPC()
```

***

