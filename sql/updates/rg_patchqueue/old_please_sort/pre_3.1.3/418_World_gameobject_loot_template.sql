-- 0000630: PVE - NORDEND - B�rde eines Helden --
DELETE FROM `gameobject` WHERE `id`= 190777;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(584318, 190777, 571, 1, 1, 5644, 3793.86, -93.8731, 5.14449, 0, 0, 0.539083, -0.842253, 25, 0, 1);
DELETE FROM `creature` WHERE `id`= 28659;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(3467914, 28659, 571, 1, 1, 0, 0, 5637.05, 3792.13, -93.7608, 5.35498, 25, 0, 0, 136548, 37250, 0, 0);

-- 0000340: Man braucht schon einen starken Magen... --
DELETE FROM `creature_questrelation` WHERE quest=12116;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('26886', '12116');

-- 0000344: Opfer m�ssen erbracht werden --
DELETE FROM `creature_loot_template` WHERE `item`=35806;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES ('26544', '35806', '-100', '1', '0', '1', '1', '0', '0', '0');

-- 0000395: Der peinliche Vorfall -- 
DELETE FROM `gameobject_loot_template`WHERE`entry`=190779;
INSERT INTO `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES ('190779', '39264', '-100', '1', '0', '1', '1', '0', '0', '0');