-- 0000329: Ein kleiner Ersatz 
UPDATE `creature_loot_template` SET `ChanceOrQuestChance`=-11 WHERE `entry`=27131 AND `item`=37020;

-- 0000648: SCHERBENWELT - Nazans Kopf 
DELETE FROM `creature_loot_template` WHERE `item`=23901;
INSERT INTO `creature_loot_template` VALUES
(17537, 23901, -100, 1, 0, 1, 1, 0, 0, 0);