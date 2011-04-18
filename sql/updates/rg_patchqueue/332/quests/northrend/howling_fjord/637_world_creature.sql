-- Kapitän Ellis , Fjord
DELETE FROM `creature` WHERE `guid` IN (2700031);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700031, 24910, 571, 1, 1, 0, 0, 111.05, -3702.67, 1.06, 0.6, 180, 0, 0, 12175, 0, 0, 0);
