-- Zul Drak: Amphitheater der Agonie Questreihe - doppelte Quest weg
-- 0000635-0000640: Das Amphitheater der Agonie:
DELETE FROM `creature_questrelation` WHERE `quest`=12954;

-- 0000605: NORDEND - Therapie
-- 0000626: PVE - Harkor
DELETE FROM `creature_questrelation` WHERE `id`=23999;
INSERT INTO `creature_questrelation` VALUES 
(23999, 12113),
(23999, 12114);
DELETE FROM `creature_involvedrelation` WHERE `id`=23999;
INSERT INTO `creature_involvedrelation` VALUES 
(23999, 12082),
(23999, 12113),
(23999, 12114);