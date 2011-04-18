DELETE FROM `creature_ai_scripts` WHERE `id` IN (2600040,2600041,2600042);
INSERT INTO `creature_ai_scripts` VALUES
	 (2600040, 33687, 2, 0, 100, 0, 90, 70, 0, 0, 12, 33695, 1, 60000, 0, 0, 0, 0, 0, 0, 0, 0, 'Bedrohung von oben - spawn'),
	 
	 (2600041, 33687, 2, 0, 100, 0, 60, 40, 0, 0,
     12, 33695, 1, 60000,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Bedrohung von oben - spawn2'),
	 
	 (2600042, 33687, 2, 0, 100, 0, 30, 10, 0, 0,
     12, 33695, 1, 60000,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Bedrohung von oben - spawn3');
	 
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry`=33695;
UPDATE `creature_template` SET `AIname`='EventAI' WHERE `entry`=33687;
-- Toxic Tunnel-Gift

DELETE FROM `creature_ai_scripts` WHERE `id`=2600043;
INSERT INTO `creature_ai_scripts` VALUES
	 
	 (2600043, 16400, 1, 0, 100, 7, 3000, 5000, 3000, 5000,
     11, 28369, 0, 0,
     0, 0, 0, 0,
     0, 0, 0, 0,
     'Toxic Tunnel-Gift');