-- Sylvanas Spawnfix
DELETE FROM `creature` WHERE guid =2574435 AND id =10181;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (2574435, 10181, 0, 1, 1, 0, 1290, 1288.73, 314.378, -57.3209, 1.37838, 25, 0, 0, 5578000, 85160, 0, 0);

