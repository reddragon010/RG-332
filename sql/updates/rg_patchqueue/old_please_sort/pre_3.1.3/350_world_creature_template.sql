DELETE FROM `creature_template` WHERE `entry` IN (2600000, 2600001, 26266, 26425, 26447);

-- Krieger und Schamanen der Drakkari fix (595 und 596)
INSERT INTO `creature_template` (`entry`, `heroic_entry`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES 
(2600000, 0, 0, 0, 24443, 0, 0, 0, 'Drakkari Shaman', '', '', 73, 73, 7952, 7952, 7654, 7654, 6126, 190, 190, 0, 1, 1, 0, 270, 395, 0, 143, 1, 1500, 0, 8, 4, 0, 0, 0, 0, 0, 0, 255, 380, 37, 7, 0, 26447, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1178, 1963, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 755, 0, 262216, ''),
(2600001, 0, 0, 0, 24418, 0, 0, 0, 'Drakkari Warrior', '', '', 73, 73, 9940, 9940, 0, 0, 7618, 190, 190, 0, 1, 1, 0, 316, 450, 0, 320, 1, 2000, 0, 1, 4, 0, 0, 0, 0, 0, 0, 278, 413, 58, 7, 0, 26425, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1172, 1954, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 753, 0, 262216, ''),
(26447, 0, 0, 0, 24443, 0, 0, 0, 'Drakkari Shaman', '', '', 73, 73, 7952, 7952, 7654, 7654, 6126, 16, 16, 0, 1, 1, 0, 270, 395, 0, 143, 1, 1500, 0, 8, 0, 0, 0, 0, 0, 0, 0, 255, 380, 37, 7, 0, 26447, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1178, 1963, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 755, 0, 0, ''),
(26425, 0, 0, 0, 24418, 0, 0, 0, 'Drakkari Warrior', '', '', 73, 73, 9940, 9940, 0, 0, 7618, 16, 16, 0, 1, 1, 0, 316, 450, 0, 320, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 278, 413, 58, 7, 0, 26425, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1172, 1954, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 753, 0, 0, ''),

-- Heigarr der Schreckliche fix (242)
(26266, 0, 0, 0, 25668, 0, 0, 0, 'Heigarr the Horrible', '', '', 70, 70, 8982, 8982, 0, 0, 5886, 1771, 1771, 0, 1, 1, 0, 275, 386, 0, 276, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 26266, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 41989, 0, 0, 0, 0, 0, 0, 1, 591, 0, 0, '');

-- Hippogryph des Silberbunds
UPDATE `creature_template` SET `faction_H`=2129, `faction_A`=2129 WHERE `entry`=30281;

DELETE FROM `creature` WHERE `guid` IN (2600020, 2600021, 2600023, 2600022, 102839, 100963, 100964);

-- Krieger und Schamanen der Drakkari fix (595 und 596)
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES 
(2600020, 2600000, 571, 1, 1, 24443, 0, 3246.88, -2275.95, 108.704, 4.7822, 300, 0, 0, 7952, 7654, 0, 0),
(2600021, 2600001, 571, 1, 1, 24418, 0, 3254.28, -2275.65, 108.744, 4.67748, 300, 0, 0, 9940, 0, 0, 0),
(2600022, 2600001, 571, 1, 1, 24418, 0, 3258.14, -2275.75, 108.703, 4.76475, 300, 0, 0, 9940, 0, 0, 0),

 -- Heigarr der Schreckliche fix (242)
(2600023, 26266, 571, 1, 1, 25668, 0, 2675.33, 4646.51, 0.09, 0, 300, 0, 0, 8982, 0, 0, 0);

DELETE FROM `item_required_target` WHERE `entry`=36956;
INSERT INTO `item_required_target` (`entry`, `type`, `targetEntry`) VALUES (36956, 2, 26616);
INSERT INTO `item_required_target` (`entry`, `type`, `targetEntry`) VALUES (36956, 2, 26643);