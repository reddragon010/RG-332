-- Sturmbö
DELETE FROM `creature` WHERE `guid` IN (2700108);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700108, 26045, 571, 1, 1, 0, 0, 3394.88, 4138.87, 18.05, 5.69, 260, 0, 0, 9473, 0, 0, 0);