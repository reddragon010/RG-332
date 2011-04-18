-- Add mob for quest http://www.wowhead.com/?quest=11625

DELETE FROM `creature` WHERE `id`= 26451;

INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(26451, 571, 1, 2, 0, 549, 1493.22, 5402.46, 38.1351, 2.55868, 25, 0, 0, 8982, 0, 0, 0);
