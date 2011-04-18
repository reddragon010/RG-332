-- 0000822: NODEND - Der Teilzeitj�ger --
DELETE FROM `creature_loot_template` WHERE`item`=38703;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
(28097, 38703, -100, 1, 0, 1, 1, 0, 0, 0);

-- 0000725: Der w�tende Gorloc -- 
DELETE FROM `creature` WHERE`id`= 28122;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(3468270, 28122, 571, 1, 1, 0, 0, 5643.06, 4554.28, -134.367, 1.29681, 25, 0, 0, 11400, 0, 0, 0);
