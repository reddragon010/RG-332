-- Fixes some spell areas for http://www.wowhead.com/?quest=11730

DELETE FROM `spell_area` WHERE `spell` = 46023;

INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_active`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`) VALUES
(46023, 4035, 0, 0, 0, 0, 0, 2, 0),
(46023, 4036, 0, 0, 0, 0, 0, 2, 0),
(46023, 4116, 0, 0, 0, 0, 0, 2, 0),
(46023, 4146, 0, 0, 0, 0, 0, 2, 0);

