-- fix area spell (borean tundra)
DELETE FROM `spell_area` WHERE `area` IN (4028, 4269);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_active`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`) VALUES (54119, 4028, 0, 0, 0, 0, 0, 2, 1);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_active`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`) VALUES (54119, 4269, 0, 0, 0, 0, 0, 2, 1);
