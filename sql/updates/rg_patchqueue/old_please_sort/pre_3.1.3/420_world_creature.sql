DELETE FROM `creature` WHERE `id` IN (30404,30403,24785,29975,26405,30924,31016);
DELETE FROM `creature` WHERE `guid` IN (7137554);
INSERT INTO `creature` VALUES
-- 0000682: NORDEND - Schrubbseife
(2600030, 24785, 571, 1, 1, 24932, 0, -40.407, -3288.58, -9.165, 5.2, 300, 5, 0, 9291, 0, 0, 1),

-- 0000686: Tapetenwechsel Questabgabe nicht möglich
(3467668, 29975, 571, 1, 1, 25796, 0, 6926.69, -1534.97, 836.055, 4.80467, 300, 0, 0, 12175, 0, 0, 0),

-- 0000674: NORDEND - Der Eisenthan und sein Amboss
(2600031, 26405, 571, 1, 1, 25794, 0, 3317.38, -5113.14, 300.46, 3.85, 300, 0, 0, 12800, 0, 0, 0),

-- Vorquestreihe zur ArenaQuest in Eiskrone
-- Das Ganze ist größer als die Summe seiner Teile
(2600032, 30404, 571, 1, 1,27027, 0, 8038.025, 3351.07, 632.40, 4.0, 100, 0, 0, 12800, 7988, 0, 0),
-- Nicht so ehrenhafter Kampf
(2600033, 30924, 571, 1, 1,18250, 0, 7223.48, 3641.61, 808.93, 6.3, 100, 0, 0, 50400, 0, 0, 0),
-- Rache der Banshee
(2600034, 31016, 571, 1, 1,27431, 0, 7082.26, 4359.37, 871.87, 4.5, 100, 0, 0, 252200, 3994, 0, 0);

-- Update alte fixes
UPDATE `creature` SET `id`=23999 WHERE `id`=26884;
UPDATE `creature` SET `modelid`=27562 WHERE `id`=31283;

