-- fix quest Jormuttar is Soo Fat...
DELETE FROM `creature_ai_scripts` WHERE `id` in (3029201, 3036601);
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`)
VALUES 
(3036601, 30366 , 11, 0, 100, 0, 0, 0, 0, 0, 12, 30340, 1, 30000, 0, 0, 0, 0, 0, 0, 0, 0, 'Lure Jormuttar Bunny - summons Jormuttar'),
(3029201, 30292, 8, 0, 100, 1, 56562, -1, 0, 0, 11, 56566, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Create Bear Flank');
DELETE FROM `creature` WHERE `id`=30292;
INSERT INTO `creature`(`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) 
VALUES (2300084, 30292, 571, 3, 1, 0, 0, 7304.461914, -2109.303467, 774.614319, 3.437933, 180, 0, 0, 1, 1, 1, 0);
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry` IN (30366,30292);
UPDATE `creature_template` SET `flags_extra`=2 WHERE `entry`=30292;