-- Aktivierungsschalter Theta
DELETE FROM `gameobject` WHERE `guid` IN (2700070);

INSERT INTO `gameobject` 
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`)
VALUES
   (2700070, 190509, 571, 1, 1, 5751.26, 3049.02, 287.98, 1.72, 0, 0, 0, 0, 240, 0, 1);