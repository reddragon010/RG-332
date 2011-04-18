-- fix some gobject respawn times from 300 to 30 sec in borean tundra start areas
DELETE FROM `gameobject` WHERE `id` IN ( 187980, 188131, 188120 );
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (57806, 187980, 571, 1, 1, 2235.06, 5256, 3.52685, 0.488691, 0, 0, 0, 1, 30, 100, 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (60631, 188120, 571, 1, 1, 2656.25, 5356.87, 34.4308, 2.61799, 0, 0, 0, 1, 30, 100, 1);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (60980, 188131, 571, 1, 1, 2373.8, 5002.74, -37.3344, -2.56563, 0, 0, 0, 1, 30, 100, 1);
