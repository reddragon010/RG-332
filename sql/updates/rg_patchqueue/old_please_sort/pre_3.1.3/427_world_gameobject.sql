-- missing south valve for http://de.wowhead.com/?quest=11788

DELETE FROM `gameobject` WHERE `id`=187987 AND `guid`=3457176;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(3457176, 187987, 571, 1, 1, 3792, 4809, -11.5, 1.5, 0, 0, 0.0331839, 0.999449, 25, 0, 1);
