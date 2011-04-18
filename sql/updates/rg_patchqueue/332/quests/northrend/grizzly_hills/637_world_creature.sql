-- Petrov , Grizzlyhügel
DELETE FROM `creature` WHERE `guid` IN (2700030);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700030, 26932, 571, 1, 1, 0, 0, 4706.12, -4055.00, 219.82, 4.11, 180, 0, 0, 12175, 0, 0, 0);
