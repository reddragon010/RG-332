-- Divine Guardian
DELETE FROM `spell_proc_event` WHERE `entry` in (53527, 53530);

INSERT INTO `spell_proc_event` (`entry`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`procFlags`,`procEx`,`ppmRate`,`CustomChance`,`Cooldown`) VALUES
(53527,1,10,0,0,0x0004,0x0400,0x0001,0,100,0),
(53530,1,10,0,0,0x0004,0x0400,0x0001,0,100,0);

