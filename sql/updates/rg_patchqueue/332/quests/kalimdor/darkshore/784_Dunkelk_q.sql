-- Gurgelbacke
DELETE FROM `creature` WHERE `guid` IN (2700107);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700107, 10323, 1, 1, 1, 0, 0, 4987.12, 576.89, 1.8, 1.7, 180, 0, 0, 517, 0, 0, 0);