-- 0000343: Ohne Fleisch kein Preis 
DELETE FROM `creature_questrelation` WHERE `quest`=12113;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('26884', '12113');

-- 0000351: Therapie
DELETE FROM `creature_questrelation` WHERE `quest`=12114;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES ('26884', '12114');