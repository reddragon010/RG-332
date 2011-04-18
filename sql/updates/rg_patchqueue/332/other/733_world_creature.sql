-- Sirana Iceshriek
DELETE FROM `creature` WHERE id = 29794;
INSERT INTO `creature` VALUES (NULL, 29794, 571, 1, 1, 0, 0, 7031.000000, 68.895699, 1019.570007, 0.911945, 300, 0, 0, 126000, 19970, 0, 0);
UPDATE `creature_template` SET mindmg = 422, maxdmg = 586, attackpower = 642, faction_A = 14, faction_H = 14, dmg_multiplier = 4.6 WHERE entry = 29794;
