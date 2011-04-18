-- Ungetuem der Knochenmalmer damage fix
DELETE FROM `creature_template` WHERE entry = 23196;
INSERT INTO `creature_template` (`entry`, `heroic_entry`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, 
`subname`, `IconName`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, 
`scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, 
`dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, 
`type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, 
`spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, 
`MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, 
`movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES (23196, 0, 0, 0, 21490, 0, 0, 0, 'Bonechewer 
Behemoth', '', NULL, 72, 72, 464940, 464940, 0, 0, 7387, 1813, 1813, 0, 1, 1, 1, 8000, 12000, 0, 6000, 1, 2000, 0, 1, 32832, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
7, 72, 23196, 0, 0, 0, 0, 0, 0, 0, 0, 41272, 8269, 41274, 41277, 0, 0, 0, 0, 0, 0, 6865, 13135, 'EventAI', 0, 3, 63, 10, 0, 0, 0, 0, 0, 0, 0, 169, 1, 0, 
547565567, 0, '');

-- Kaempfer der Knochenmalmer
UPDATE `creature_template` SET `dmg_multiplier`='1' WHERE (`entry`='23239') LIMIT 1;
-- Mutierter Muskelprotz
UPDATE `creature_template` SET `dmg_multiplier`='1' WHERE (`entry`='23222') LIMIT 1;
