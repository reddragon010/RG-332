-- adding missing dalaran teleporter
DELETE FROM `gameobject` WHERE `id`=191230;
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(191230, 571, 1, 1, 5731.23, 1014.9, 174.48, 0.859632, 0, 0, 0.416703, 0.909043, 25, 0, 1);