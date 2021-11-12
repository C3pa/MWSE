--- @meta

--- Represents a loaded ESM, ESP, or ESS file.
--- @class tes3gameFile
--- @field author string *Read-only*. The file's author.
--- @field cellName string *Read-only*. The current cell, from a save game.
--- @field currentHealth number *Read-only*. The player's health, from a save game.
--- @field day number *Read-only*. The current day, from a save game.
--- @field daysPassed number *Read-only*. The number of days passed, from a save game.
--- @field description string *Read-only*. The description of the file.
--- @field filename string *Read-only*. The simple filename.
--- @field fileSize number *Read-only*. The size of the file.
--- @field gameHour number *Read-only*. The current game hour, from a save game.
--- @field highestFormID number *Read-only*. No description yet available.
--- @field masters table *Read-only*. An array-style table of the tes3gameFiles that this is dependent upon.
--- @field maxHealth number *Read-only*. The player's maximum health, from a save game.
--- @field modifiedTime string *Read-only*. The timestamp that the file was modified.
--- @field month number *Read-only*. The current month, from a save game.
--- @field path string *Read-only*. The path to the file.
--- @field playerName string *Read-only*. The player's name, from a save game.
--- @field year number *Read-only*. The current year, from a save game.
tes3gameFile = {}

--- Deletes the file.
function tes3gameFile:deleteFile() end

