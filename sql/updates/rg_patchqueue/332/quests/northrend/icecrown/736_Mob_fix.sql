-- Aufseher Narvir
DELETE FROM `creature` WHERE `guid` IN (2700085);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700085, 30299, 571, 1, 1, 0, 0, 7309.03, -728.16, 791.60, 4.11, 180, 0, 0, 12175, 0, 0, 0);