DELETE FROM `creature_ai_scripts` WHERE `id` IN (2600021,2600022,2600023,2600024,2600025,2600026,2600027,2600028,2600029,2600030,2600031,2600032,2600033,2600034,2600035);
INSERT INTO `creature_ai_scripts` 
	(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, 
	`action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, 
	`action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, 
	`action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, 
	`comment`)
VALUES
-- Das Ganze ist größer als die Summe seiner Teile
	 (2600021, 30404, 0, 0, 100, 1, 10000, 10000, 30000, 30000,
     11, 31730, 0, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Dr. Maböse - heilen'),
	 
	 (2600022, 30404, 0, 0, 100, 1, 15000, 15000, 30000, 30000,
     11, 61143, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Dr. Maböse - Irres Zerhacken'),
	 
	 (2600023, 30404, 0, 0, 100, 1, 20000, 20000, 30000, 30000,
     11, 61146, 4, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Dr. Maböse - Schleimstrahl'),
	 
-- Nicht so ehrenhafter Kampf
	 (2600024, 30924, 0, 0, 100, 1, 10000, 10000, 60000, 60000,
     11, 60108, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Besessener Iskalder - Heldenhafter Sprung'),
	 
	 (2600025, 30924, 0, 0, 100, 1, 15000, 15000, 10000, 20000,
     11, 57846, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Besessener Iskalder - Heldenhafter Stoß'),
	 
	 (2600026, 30924, 0, 0, 100, 1, 20000, 20000, 15000, 15000,
     11, 15496, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Besessener Iskalder - Spalten'),

	 (2600027, 30924, 0, 0, 100, 1, 5000, 5000, 30000, 30000,
     11, 60121, 0, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Besessener Iskalder - Uralter Fluch'),
	 
-- Oberthan Balargarde <Herr von Jotunheim>
	 (2600028, 31016, 0, 0, 100, 1, 5000, 5000, 60000, 60000,
     11, 61085, 4, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Oberthan Balargarde - Blizzard'),
	 
	 (2600029, 31016, 0, 0, 100, 1, 15000, 15000, 60000, 60000,
     11, 15043, 4, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Oberthan Balargarde - Heldenhafter Stoß'),
	 
	 (2600030, 31016, 0, 0, 100, 1, 20000, 20000, 60000, 60000,
     11, 60108, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Oberthan Balargarde - Heldenhafter Sprung'),

	 (2600031, 31016, 0, 0, 100, 1, 25000, 25000, 60000, 60000,
     11, 61076, 0, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Oberthan Balargarde - Wirbelwind'),
	 
-- Prinz Sandoval
	 (2600032, 14688, 0, 0, 100, 1, 5000, 5000, 60000, 60000,
     11, 61163, 0, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Prinz Sandoval - Feuernova'),
	 
	 (2600033, 14688, 0, 0, 100, 1, 15000, 15000, 60000, 60000,
     11, 61162, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Prinz Sandoval - Einhüllender Stoß'),
	 
	 (2600034, 14688, 0, 0, 100, 1, 20000, 20000, 60000, 60000,
     11, 61145, 1, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Prinz Sandoval - Funkenregen'),

	 (2600035, 14688, 0, 0, 100, 1, 25000, 25000, 60000, 60000,
     28, 0, 61147, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Prinz Sandoval - Funkenregen aus');