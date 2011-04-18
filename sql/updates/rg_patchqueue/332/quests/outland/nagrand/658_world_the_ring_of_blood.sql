-- Fixes issue http://bugtracker.rising-gods.de/view.php?id=1127
-- This fix is based on the posts of Malcrom and Brian.
-- "The Ring of Blood" quest chain in Nagrand requires script to issue quest complete
UPDATE `quest_template` SET `specialflags`=`specialflags`|2 WHERE `entry` IN (9962,9967,9970,9972,9973,9977);

-- Update creature 9962 "Brokentoe" to use EventAI for quest The Ring of Blood: Brokentoe.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18398;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1839801;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1839801,18398,6,0,100,0,0,0,0,0,26,9962,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');
-- Update creature 9967 "The Blue Brothers" to use EventAI for quest The Ring of Blood: The Blue Brothers.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18399;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1839901;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1839901,18399,6,0,100,0,0,0,0,0,26,9967,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');
-- Update creature 9970 "Rokdar the Sundered Lord" to use EventAI for quest The Ring of Blood: Rokdar the Sundered Lord.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18400;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1840001;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1840001,18400,6,0,100,0,0,0,0,0,26,9970,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');
-- Update creature 9972 "Skra'gath" to use EventAI for quest The Ring of Blood: Skra'gath.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18401;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1840101;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1840101,18401,6,0,100,0,0,0,0,0,26,9972,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');
-- Update creature 9973 "The Warmaul Champion" to use EventAI for quest The Ring of Blood: The Warmaul Champion.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18398;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1840201;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1840201,18402,6,0,100,0,0,0,0,0,26,9973,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');
-- Update creature 9977 "The Final Challenge" to use EventAI for quest The Ring of Blood: The Final Challenge.
UPDATE `creature_template` SET `AIName`= 'EventAI' WHERE `entry`=18069;
-- EAI scripts
DELETE FROM `creature_ai_scripts` WHERE `id`=1806901;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(1806901,18069,6,0,100,0,0,0,0,0,26,9977,0,0,0,0,0,0,0,0,0,0, 'Give quest credit on death');

-- set required creature to 2 for The Blue Brothers
UPDATE `quest_template` SET `ReqCreatureOrGOId1` = '18399', `ReqCreatureOrGOCount1` = '2' WHERE `entry` =9967;

