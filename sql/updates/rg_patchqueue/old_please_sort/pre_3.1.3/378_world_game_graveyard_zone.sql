-- fix of Dragonblight, Forsaken East Graveyard 

DELETE FROM `game_graveyard_zone` WHERE `id` = 1309;

INSERT INTO `game_graveyard_zone` (`id`, `ghost_zone`, `faction`) VALUES (1309, 65, 67);