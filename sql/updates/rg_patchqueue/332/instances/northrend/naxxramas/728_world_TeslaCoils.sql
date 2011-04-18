DELETE FROM `creature` WHERE `guid` IN (2300002,2300003);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) 
VALUES(2300002,16218,533,3,1,0,0,3527.39,-2952.32,322,0,300,0,0,0,0,0,0),
(2300003,16218,533,3,1,0,0,3487.06,-2911.88,322,0,300,0,0,0,0,0,0);
UPDATE creature_template SET faction_A=35, faction_H=35, unit_flags=unit_flags|2, flags_extra=2/*flags_extra|2&~128*/ WHERE entry=16218; 