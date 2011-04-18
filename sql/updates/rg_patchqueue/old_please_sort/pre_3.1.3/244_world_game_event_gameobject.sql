-- Winter Veil Gifts
DELETE FROM `game_event_gameobject` WHERE `guid` in (574050, 574505, 583683, 583754, 584144, 584201);
INSERT INTO `game_event_gameobject` (`guid`, `event`) VALUES 
('574050', '124'),
('574505', '124'), 
('583683', '124'), 
('583754', '124'), 
('584144', '124'), 
('584201', '124');
