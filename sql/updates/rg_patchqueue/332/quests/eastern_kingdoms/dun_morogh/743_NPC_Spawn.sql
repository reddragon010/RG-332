-- Feldmarschall Schneefall <Kommandant der Kriegsanstrengungen>
DELETE FROM `creature` WHERE `guid` IN (2700087);

INSERT INTO `creature`
   (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES 
   (2700087, 15701, 0, 1, 1, 0, 0, -4960.31, -1200.56, 501.65, 0.68, 180, 0, 0, 12175, 0, 0, 0);