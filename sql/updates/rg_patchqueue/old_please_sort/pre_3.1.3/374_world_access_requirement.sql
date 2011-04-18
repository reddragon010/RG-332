-- Last Rites Portal 

DELETE FROM `access_requirement` WHERE `id` = 9000 AND `comment` = 'Last Rites Portal';

INSERT INTO `access_requirement` (`id`, `level_min`, `heroic_level_min`, `level_max`, `item`, `item2`, `heroic_key`, `heroic_key2`, `quest_done`, `quest_failed_text`, `heroic_quest_done`, `heroic_quest_failed_text`, `comment`) VALUES ('9000', '0', '0', '0', '0', '0', '0', '0', '0', NULL, '0', NULL, 'Last Rites Portal');