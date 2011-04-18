-- corpse explode(49618, 59809H)  damage
DELETE FROM spell_linked_spell WHERE spell_trigger in(49555,59807);
insert into `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) values(49555,49618,1, "corpse explode");
insert into `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) values(59807,59809,1, "corpse explode");