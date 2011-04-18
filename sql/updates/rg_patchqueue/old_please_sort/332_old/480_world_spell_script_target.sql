-- corpse explode(49555, 59807H)  visual targets corpse of Drakkari Invaders (27709,27753) 
DELETE FROM spell_script_target WHERE entry in(49555,59807);
insert into `spell_script_target` (`entry`,`type`,`targetEntry`) values(49555,2,27709);
insert into `spell_script_target` (`entry`,`type`,`targetEntry`) values(49555,2,27753);
insert into `spell_script_target` (`entry`,`type`,`targetEntry`) values(59807,2,27709);
insert into `spell_script_target` (`entry`,`type`,`targetEntry`) values(59807,2,27753);