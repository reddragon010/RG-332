-- Remove vendor Template
DELETE FROM `npc_vendor` WHERE `entry` = 24396; -- from Forest Frog - 24396( Zul Aman)
DELETE FROM `npc_vendor` WHERE `entry` = 24408; -- Gunther
DELETE FROM `npc_vendor` WHERE `entry` = 24409; -- Kyren

-- Add Vendor Templates to 
-- Forest Frog - 24396( Zul Aman)
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (24396, 27666, 12, 120, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (24396, 27667, 10, 120, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (24396, 33926, 1, 3600, 0);
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES (24396, 33928, 1, 3600, 0);

-- Gunter (Food) 24408
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(24408, 8948, 0, 0, 0),
(24408, 27859, 0, 0, 0),
(24408, 27657, 12, 120, 0),
(24408, 29453, 0, 0, 0),
(24408, 22829, 4, 120, 0);

-- Kyren (Reagents) 24409
INSERT INTO `npc_vendor` (`entry`, `item`, `maxcount`, `incrtime`, `ExtendedCost`) VALUES
(24409, 16583, 0, 0, 0),
(24409, 17029, 0, 0, 0),
(24409, 17030, 0, 0, 0),
(24409, 17033, 0, 0, 0),
(24409, 21177, 0, 0, 0),
(24409, 22147, 0, 0, 0),
(24409, 22148, 0, 0, 0);
