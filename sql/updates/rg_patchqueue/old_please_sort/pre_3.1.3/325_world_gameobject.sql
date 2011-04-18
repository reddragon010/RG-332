-- add gameobject for http://wowdata.buffed.de/?q=11650

DELETE FROM `gameobject` WHERE `id`= 187697;

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(187697, 571, 1, 1, 4009.03, 4859.7, -12.5006, 0.73161, 0, 0, 0.357701, 0.933836, 25, 0, 1);
