-- Paladin und Hexenmeister Mountfixes
-- Remove skill-learn-spells
DELETE FROM `npc_trainer` WHERE `spell`=33388 AND `entry` in (16275, 16679, 16680, 16681, 20406, 23128, 927, 17509, 17483, 17121, 16761, 8140, 5492, 5491, 5149, 5148, 5147, 1232, 928, 17844, 461, 5172, 5173, 5495, 5496, 5612, 16266, 16646, 16647, 16648, 5171, 4565, 906, 988, 2127, 3172, 3324, 3325, 3326, 4563, 4564, 23534);
DELETE FROM `npc_trainer` WHERE `spell`=33391 AND `entry` in (16275, 16679, 16680, 16681, 20406, 23128, 927, 17509, 17483, 17121, 16761, 8140, 5492, 5491, 5149, 5148, 5147, 1232, 928, 17844, 461, 5172, 5173, 5495, 5496, 5612, 16266, 16646, 16647, 16648, 5171, 4565, 906, 988, 2127, 3172, 3324, 3325, 3326, 4563, 4564, 23534);
-- Horde Paladin Erstes Mount
DELETE FROM `npc_trainer` WHERE `spell`=34768 AND `entry` in (16275, 16679, 16680, 16681, 20406, 23128);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16275, 34768, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16679, 34768, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16680, 34768, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16681, 34768, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (20406, 34768, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (23128, 34768, 100000, 0, 0, 30);
-- Horde Paladin Zweites Mount
-- Remove wrong spell
DELETE FROM `npc_trainer` WHERE `spell`=34767;
DELETE FROM `npc_trainer` WHERE `spell`=34766 AND `entry` in (16275, 16679, 16680, 16681, 20406, 23128);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16275, 34766, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16679, 34766, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16680, 34766, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16681, 34766, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (20406, 34766, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (23128, 34766, 200000, 0, 0, 61);
-- Allianz Paladin Erstes Mount
DELETE FROM `npc_trainer` WHERE `spell`=13820 AND `entry` in (927, 17509, 17483, 17121, 16761, 8140, 5492, 5491, 5149, 5148, 5147, 1232, 928, 17844);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (927, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17509, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17483, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17121, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16761, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (8140, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5492, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5491, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5149, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5148, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5147, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (1232, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (928, 13820, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17844, 13820, 100000, 0, 0, 30);
-- Allianz Paladin Zweites Mount
-- Remove wrong spell
DELETE FROM `npc_trainer` WHERE `spell`=23214;
DELETE FROM `npc_trainer` WHERE `spell`=23215 AND `entry` in (927, 17509, 17483, 17121, 16761, 8140, 5492, 5491, 5149, 5148, 5147, 1232, 928, 17844);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (927, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17509, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17483, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17121, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16761, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (8140, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5492, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5491, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5149, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5148, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5147, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (1232, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (928, 23215, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (17844, 23215, 200000, 0, 0, 61);
-- Horde&Allianz Hexenmeister Erstes Mount
DELETE FROM `npc_trainer` WHERE `spell`=1710 AND `entry` in (461, 5172, 5173, 5495, 5496, 5612, 16266, 16646, 16647, 16648, 5171, 4565, 906, 988, 2127, 3172, 3324, 3325, 3326, 4563, 4564, 23534);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (461, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5172, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5173, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5495, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5496, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5612, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16266, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16646, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16647, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16648, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5171, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4565, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (906, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (988, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (2127, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3172, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3324, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3325, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3326, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4563, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4564, 1710, 100000, 0, 0, 30);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (23534, 1710, 100000, 0, 0, 30);
-- Horde&Allianz Hexenmeister Zweites Mount
-- remove wrong spell
DELETE FROM `npc_trainer` WHERE `spell`=23161;
DELETE FROM `npc_trainer` WHERE `spell`=23160 AND `entry` in (461, 5172, 5173, 5495, 5496, 5612, 16266, 16646, 16647, 16648, 5171, 4565, 906, 988, 2127, 3172, 3324, 3325, 3326, 4563, 4564, 23534);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (461, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5172, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5173, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5495, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5496, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5612, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16266, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16646, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16647, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (16648, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (5171, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4565, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (906, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (988, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (2127, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3172, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3324, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3325, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (3326, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4563, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (4564, 23160, 200000, 0, 0, 61);
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES (23534, 23160, 200000, 0, 0, 61);
