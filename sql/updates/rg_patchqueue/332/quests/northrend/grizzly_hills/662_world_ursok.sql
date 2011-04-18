DELETE FROM `creature` WHERE `guid` IN (2700067);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700067, 26633, 571, 1, 1, 0, 0, 4902.24, -3846.81, 337.50, 5.13, 160, 0, 0, 210000, 0, 0, 0);
