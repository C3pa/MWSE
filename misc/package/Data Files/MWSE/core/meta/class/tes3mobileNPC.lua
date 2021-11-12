--- @meta

--- A mobile object for an NPC.
--- @class tes3mobileNPC : tes3mobileActor, tes3mobileObject
--- @field acrobatics tes3skillStatistic *Read-only*. Direct access to the NPC's acrobatics skill statistic.
--- @field alchemy tes3skillStatistic *Read-only*. Direct access to the NPC's alchemy skill statistic.
--- @field alteration tes3skillStatistic *Read-only*. Direct access to the NPC's alteration skill statistic.
--- @field armorer tes3skillStatistic *Read-only*. Direct access to the NPC's armorer skill statistic.
--- @field athletics tes3skillStatistic *Read-only*. Direct access to the NPC's athletics skill statistic.
--- @field axe tes3skillStatistic *Read-only*. Direct access to the NPC's axe skill statistic.
--- @field block tes3skillStatistic *Read-only*. Direct access to the NPC's block skill statistic.
--- @field bluntWeapon tes3skillStatistic *Read-only*. Direct access to the NPC's blunt weapon skill statistic.
--- @field conjuration tes3skillStatistic *Read-only*. Direct access to the NPC's conjuration skill statistic.
--- @field destruction tes3skillStatistic *Read-only*. Direct access to the NPC's destruction skill statistic.
--- @field enchant tes3skillStatistic *Read-only*. Direct access to the NPC's enchant skill statistic.
--- @field flySpeed number *Read-only*. The calculated fly movement speed.
--- @field forceJump boolean Toggle flag for if the NPC jumps.
--- @field forceMoveJump boolean Toggle flag for if the NPC moves and jumps.
--- @field forceRun boolean Toggle flag for if the NPC runs.
--- @field forceSneak boolean Toggle flag for if the NPC sneaks.
--- @field handToHand tes3skillStatistic *Read-only*. Direct access to the NPC's hand to hand skill statistic.
--- @field heavyArmor tes3skillStatistic *Read-only*. Direct access to the NPC's heavy armor skill statistic.
--- @field illusion tes3skillStatistic *Read-only*. Direct access to the NPC's illusion skill statistic.
--- @field lightArmor tes3skillStatistic *Read-only*. Direct access to the NPC's light armor skill statistic.
--- @field longBlade tes3skillStatistic *Read-only*. Direct access to the NPC's long blade skill statistic.
--- @field marksman tes3skillStatistic *Read-only*. Direct access to the NPC's marksman skill statistic.
--- @field mediumArmor tes3skillStatistic *Read-only*. Direct access to the NPC's medium armor skill statistic.
--- @field mercantile tes3skillStatistic *Read-only*. Direct access to the NPC's mercantile skill statistic.
--- @field moveSpeed number *Read-only*. The calculated base movement speed.
--- @field mysticism tes3skillStatistic *Read-only*. Direct access to the NPC's mysticism skill statistic.
--- @field object tes3npcInstance *Read-only*. The actor object that maps to this mobile.
--- @field restoration tes3skillStatistic *Read-only*. Direct access to the NPC's restoration skill statistic.
--- @field runSpeed number *Read-only*. The calculated run movement speed.
--- @field security tes3skillStatistic *Read-only*. Direct access to the NPC's security skill statistic.
--- @field shortBlade tes3skillStatistic *Read-only*. Direct access to the NPC's short blade skill statistic.
--- @field skills table *Read-only*. An array-style table with access to the twenty seven NPC skill statistics.
--- @field sneak tes3skillStatistic *Read-only*. Direct access to the NPC's sneak skill statistic.
--- @field spear tes3skillStatistic *Read-only*. Direct access to the NPC's spear skill statistic.
--- @field speechcraft tes3skillStatistic *Read-only*. Direct access to the NPC's speechcraft skill statistic.
--- @field swimRunSpeed number *Read-only*. The calculated swim movement speed while running.
--- @field swimSpeed number *Read-only*. The calculated swim movement speed.
--- @field unarmored tes3skillStatistic *Read-only*. Direct access to the NPC's unarmored skill statistic.
--- @field walkSpeed number *Read-only*. The calculated walk movement speed.
tes3mobileNPC = {}

