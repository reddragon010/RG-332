-- Sage der Zwillinge
DELETE FROM `gameobject` WHERE `guid` IN (2700087);

INSERT INTO `gameobject` 
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`)
VALUES
   (2700087, 186831, 571, 1, 1, 963.80, -5308.20, 175.80, 1.63, 0, 0, 0, 0, 240, 0, 1);