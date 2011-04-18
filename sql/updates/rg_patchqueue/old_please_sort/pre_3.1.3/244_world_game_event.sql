-- GameEvents
DELETE FROM `game_event` WHERE `entry` in (1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 26, 124);
INSERT INTO `game_event` (`entry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES
(1, '2009-06-21 05:00:00', '2020-12-31 06:00:00', 525600, 18720, 341, 'Midsummer Fire Festival', 0),
(2, '2009-12-15 06:00:00', '2020-12-31 06:00:00', 525600, 25920, 141, 'Winter Veil', 0),
(3, '2009-02-01 04:00:00', '2020-12-31 06:00:00', 131040, 10080, 376, 'Darkmoon Faire (Terokkar Forest)', 0),
(4, '2009-03-01 11:00:00', '2020-12-31 06:00:00', 131040, 10080, 374, 'Darkmoon Faire (Elwynn Forest)', 0),
(5, '2009-01-04 12:00:00', '2020-12-31 06:00:00', 131040, 10080, 375, 'Darkmoon Faire (Mulgore)', 0),
(7, '2009-02-12 06:00:00', '2020-12-31 06:00:00', 525600, 27360, 327, 'Lunar Festival', 0),
(8, '2009-02-11 06:00:00', '2020-12-31 06:00:00', 525600, 7200, 335, 'Love is in the Air', 0),
(9, '2009-04-04 00:01:00', '2020-12-31 06:00:00', 525600, 10078, 181, 'Noblegarden', 0),
(10, '2009-05-01 00:01:00', '2020-12-31 06:00:00', 525600, 10078, 201, 'Children''s Week ', 0),
(11, '2009-09-16 00:01:00', '2020-12-31 06:00:00', 525600, 10078, 321, 'Harvest Festival', 0),
(12, '2009-10-18 04:00:00', '2020-12-31 06:00:00', 525600, 21600, 324, 'Hallow''s End', 0),
(26, '2009-09-20 00:01:00', '2020-12-31 06:00:00', 525600, 10078, 372, 'Brewfest', 0);
-- Dummy Winter Veil Event for gifts
INSERT INTO `game_event` (`entry`, `start_time`, `end_time`, `occurence`, `length`, `holiday`, `description`, `world_event`) VALUES 
('124',  '2009-12-25 00:00:00',  '2020-12-31 06:00:00',  '525600',  '11520',  '0',  'Winter Veil Gifts',  '0');
