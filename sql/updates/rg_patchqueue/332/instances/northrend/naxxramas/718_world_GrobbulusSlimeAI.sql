-- -- Fallout Slime(16290, 29388)
DELETE FROM `creature_ai_scripts` WHERE id IN (1629001,1629002);
insert into `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) values
(1629001,16290,0,0,100,2,0,0,0,0,11,27793,0,0,0,0,0,0,0,0,0,0, 'Fallout Slime - Cast Disease Cloud on Spawn'),
(1629002,16290,0,0,100,4,0,0,0,0,11,54367,0,0,0,0,0,0,0,0,0,0, 'Fallout Slime - Cast Disease Cloud on Spawn Heroic');