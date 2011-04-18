-- added missing gameobject for http://de.wowhead.com/?quest=11288

DELETE FROM `gameobject` WHERE `id`=186607;

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(186607, 571, 1, 1, 964.655, -4821.58, -116.158, 3.44472, 0, 0, 0.988537, -0.150982, 25, 0, 1);

