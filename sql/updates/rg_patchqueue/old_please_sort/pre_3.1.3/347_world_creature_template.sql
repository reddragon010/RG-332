-- fixes Rachmähne spawn
DELETE FROM `creature` WHERE `id` IN (29664);
INSERT INTO `creature` Values (2600019, 29664, 571, 1, 1, 26416, 0, 4865.03, -2515.96, 217.37, 5.2, 300, 20, 0, 106350, 0, 0, 1);

-- Fix 2. Boss in Gundrak
DELETE FROM `creature_template` WHERE `entry` IN (29573, 31367);
INSERT INTO `creature_template` VALUES (29573, 31367, 0, 0, 27028, 0, 0, 0, 'Drakkari Elemental', '', '', 1, 1, 117700, 117700, 0, 0, 9124, 16, 16, 0, 1, 1, 1, 387, 543, 0, 528, 7.5, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 324, 480, 88, 4, 104, 29573, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 10, 1, 0, 43158, 0, 0, 0, 0, 0, 164, 1, 0, 0, 0, 'boss_drakkari_elemental');
INSERT INTO `creature_template` VALUES (31367, 0, 0, 0, 27028, 0, 0, 0, 'Drakkari Elemental (1)', '', '', 82, 82, 215696, 215696, 4169, 4169, 10356, 16, 16, 0, 1, 1, 1, 488, 642, 0, 782, 13, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 363, 521, 121, 4, 104, 31367, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 16, 1, 0, 43158, 0, 0, 0, 0, 0, 164, 1, 0, 0, 0, '');

-- Fix 0000543 Das flüssige Feuer Elunes
UPDATE `quest_template` SET `ReqSpellCast1`=46770, `ReqSpellCast2`=46770, `ReqCreatureOrGOId1`=26616, `ReqCreatureOrGOId2`=26643 WHERE `entry`=12166;