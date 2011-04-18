DELETE FROM `creature` WHERE `id` IN (28496,25328,25392,26266,24717,24718,24719,24720,24750,24807,26934);
DELETE FROM `creature` WHERE `guid` IN (2600029,125693,2600028,96557,102317,2600027,2600026,2800000,2800001,2800002,2800003);

-- 0000641: Verseuchte letzte Riten 
UPDATE `creature` SET `spawntimesecs`=30 WHERE `id`=27349;

-- 0000573: PVE - NORDEND - Schweigen ist Gold 
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES 
(26169, 25328, 571, 1, 1, 23117, 0, 2896.08, 6263.66, 61.5788, 2.5, 180, 0, 0, 9610, 3309, 0, 0),

-- PVP SET Verkäufer
(125693, 34036, 1, 1, 1, 0, 0, 1671.19, -4201.64, 56.1558, 3.55233, 25, 0, 0, 11828, 0, 0, 0),

-- 0000607: NORDEND - Hohepriester Andorath
(2600025, 25392, 571, 1, 1, 23510, 0, 4105.16, 3487.16, 109.20, 2.6, 300, 0, 0, 9610, 3309, 0, 0),

-- 0000671: Fehlende Geistheiler 
(2600026, 6491, 571, 1, 1, 5233, 0, 2848.896973, 5974.019043, 114.676529, 3.462459, 60, 0, 0, 4120, 0, 0, 0),

-- 0000633: NORDEND - Verhindert das Abkommen
(2600027, 26496, 571, 1, 1, 19637, 0, 3369.0, 2612.3, 39.11, 1.72, 300, 0, 0, 7688, 7500, 0, 0),

-- Von Mike und mir:
-- Questgeber und Abgeber ZulDrak Arena-Questreihe
(2800000, 30007, 571, 1, 1, 17836, 0, 5798.22, -3018.43, 286.30, 5.2, 30, 0, 0, 10635, 0, 0, 0),
(2800001, 30009, 571, 1, 1, 12829, 0, 5788.84, -3022.85, 286.30, 5.2, 30, 0, 0, 10282, 0, 0, 0),

-- Fjord / Außenposten der Forscherliga
(2800004, 24717, 571, 3, 1, 22604, 0, 479.663, -5929.46, 308.665, 1.11701, 180, 0, 0, 7380, 0, 0, 0),
(2800005, 24718, 571, 3, 1, 22623, 0, 488.253, -5919.57, 308.755, 5.757, 180, 0, 5, 6986, 0, 0, 1),
(2800006, 24719, 571, 3, 1, 22619, 0, 467.963, -5923.52, 309.837, 3.84355, 180, 0, 5, 6.986, 0, 0, 1),
(2800007, 24720, 571, 3, 1, 22622, 0, 483.309, -5926.56, 308.664, -2.80997, 180, 0, 0, 7181, 0, 0, 0),
(2800008, 24750, 571, 3, 1, 22624, 0, 497.639, -5948.49, 314.395, 5.39307, 180, 0, 0, 7588, 0, 0, 0),
(2800009, 24807, 571, 3, 1, 22645, 0, 475.726, -5935.29, 308.804, 3.735, 180, 0, 0, 3080, 0, 0, 0),
(2800010, 26934, 571, 3, 1, 24178, 0, 488.725, -5932.58, 308.804, 2.26893, 180, 0, 0, 7380, 0, 0, 0),
-- -- -- -- --

-- 0000669: Zum Drachenjägerposten 
(2600028, 26859, 571, 1, 1, 0, 0, 4341.32, 979.273, 91.662, 5.40326, 25, 0, 0, 7860, 0, 0, 0),

-- 0000643: NPC - Zedd (Fjord) [Questreihe]
(2800002, 24145, 571, 1, 1, 22150, 0, 995.72, -4829.55, -1.06, 6.1, 30, 0, 0, 6986, 0, 0, 0),

-- Blutbanns Schicksal
(2600029, 31283, 571, 1, 1, 18343, 0, 5819.43, 2040.865, 503.31, 6.15, 300, 0, 0, 422100, 0, 0, 0),

-- 0000644: NPC - Schattenpirscher Getry (Tundra) 
(2800003, 25729, 571, 1, 1, 23335, 0, 3123.06, 6576.54, 98.0, 3.1, 30, 0, 0, 79840, 0, 0, 0);
