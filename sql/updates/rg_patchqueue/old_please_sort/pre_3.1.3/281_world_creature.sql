-- 0000361: Brigadegeneral der Allianz fehlt in Nordend 
DELETE FROM `creature` WHERE `guid`=3467658;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(3467658, 15351, 571, 1, 1, 0, 0, 5647.9, 805.027, 653.699, 5.49081, 25, 0, 0, 32810, 0, 0, 0);