DELETE FROM `creature_ai_scripts` WHERE `id` IN (2600037);
INSERT INTO `creature_ai_scripts` 
	(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, 
	`action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, 
	`action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, 
	`action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, 
	`comment`)
VALUES
-- 0000729: Brenn darauf zu helfen 
	 (2600037, 28003, 0, 0, 100, 1, 5000, 5000, 30000, 30000,
     11,52307, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Bittertidenhydra - Hydrasputum');