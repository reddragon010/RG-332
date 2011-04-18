-- 0000641: Verseuchte letzte Riten 
DELETE FROM `item_required_target` WHERE `entry`=37129;
INSERT INTO `item_required_target` (`entry`, `type`, `targetEntry`) VALUES (37129, 1, 27349);
UPDATE `item_template` SET `spellcharges_1`=0 WHERE `entry`=37129;

-- 0000332: Fotosafari 
DELETE FROM `item_required_target` WHERE `entry` IN (37125,42837);
INSERT INTO `item_required_target` (`entry`, `type`, `targetEntry`) VALUES 
(37125, 2, 26408),

-- 0000657: NORDEND - Disziplin 
(42837, 1, 30146);