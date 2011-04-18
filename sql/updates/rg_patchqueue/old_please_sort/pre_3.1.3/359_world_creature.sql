DELETE FROM `creature` where id in(25397, 25398, 25399);

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(25397, 571, 1, 1, 20559, 0, 3643.49, 5634.1, 35.9507, 1.51377, 300, 0, 0, 9610, 3309, 0, 0),
(25398, 571, 1, 1, 25979, 0, 3567.32, 5505.58, 27.012, 0.839093, 300, 0, 0, 1, 0, 0, 0),
(25399, 571, 1, 1, 25980, 0, 3683.96, 5569.8, 34.8291, 5.52323, 300, 0, 0, 1, 0, 0, 0);
