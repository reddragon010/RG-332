UPDATE `quest_start_scripts` SET `datalong2`=60000 WHERE `id` IN (2600001,2600002,2600003,2600004,2600005,2600006,2600007,2600008,2600009,2600010,2600011);
DELETE FROM `quest_start_scripts` WHERE `id` IN (2600014,2600015,2600016,2600017,2600018,2600019);
INSERT INTO `quest_start_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES 
-- Kampf bei Valhalas: Questreihe
(2600014, 0, 10, 31193, 100000, 0, 8184.293, 3463.993, 628.251, 1.130),
(2600014, 0, 10, 31191, 100000, 0, 8180.534, 3465.868, 627.633, 1.108),
(2600014, 0, 10, 31192, 100000, 0, 8176.953, 3468.930, 627.046, 0.833),
(2600014, 0, 10, 31196, 100000, 0, 8173.242, 3473.296, 626.752, 0.666),
(2600015, 0, 10, 31222, 100000, 0, 8155.166, 3489.551, 627.652, 0.362),
(2600016, 0, 10, 31242, 100000, 0, 8166.361, 3529.396, 628.926, 5.955),
(2600017, 0, 10, 31271, 100000, 0, 8218.356, 3465.990, 628.495, 2.024),
(2600018, 0, 10, 31277, 100000, 0, 8245.581, 3487.260, 628.136, 2.328),
(2600019, 0, 10, 14688, 100000, 0, 8234.026, 3560.754, 628.814, 4.123);