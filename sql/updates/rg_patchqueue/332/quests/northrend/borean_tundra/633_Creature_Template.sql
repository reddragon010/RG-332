--  Glrggl , Boreanische Tundra
DELETE FROM `creature` WHERE `guid` IN (2700022);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700022, 25203, 571, 1, 1, 0, 0, 4471.74, 6252.39, -1.523, 3.81, 160, 0, 0, 9291, 0, 0, 0);
   
   UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=25203;
   
   