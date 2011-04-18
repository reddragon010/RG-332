-- boss immune mask
UPDATE creature_template SET mechanic_immune_mask=617299803 WHERE entry IN (26668,30810,26687,30774,26693,30807,26861,30788);
-- Svala Sorrowgrave, Svala Sorrowgrave H, ritual channeler, ritual channeler hero, Ritual Target , Ritual Target H faction 
UPDATE creature_template SET faction_A=14, faction_H=14 WHERE entry IN (26668,30810,27281,30804);
-- flame brazier, flame brazier hero, Ritual Target , Ritual Target H
UPDATE creature_template SET faction_A=35, faction_H=35, flags_extra=2/*flags_extra|2&~128*/ WHERE entry IN (27273,30771); 
UPDATE creature_template SET faction_A=35, faction_H=35, flags_extra=128/*flags_extra|128&~2*/ WHERE entry IN (27327,30805); 
-- Svala Sorrowgrave, Svala Sorrowgrave H, 
UPDATE creature_template SET mindmg=350, maxdmg=450, dmg_multiplier=7.5 WHERE entry=26668; -- Svala Sorrowgrave
UPDATE creature_template SET mindmg=400, maxdmg=500, dmg_multiplier=13, equipment_id=2012 WHERE entry=30810; -- Svala Sorrowgrave H
-- Flame brazier position
UPDATE creature SET position_z=92.0833 WHERE id =27273; 
-- Ritual of the sword teleport svala position 
DELETE FROM spell_target_position WHERE id =48276;
insert into `spell_target_position` (`id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) values('48276','575','296.632','-346.075','110.63','4.6');
-- ritual target
DELETE FROM spell_script_target WHERE entry =48331;
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48331','1','27327');
-- ritual strike target, Flame Breath Trigger(skadi)
DELETE FROM spell_script_target WHERE ENTRY IN (48277,59930,48246,47593,47563);
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48277','1','0');
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48277','1','26555');
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('59930','1','26555'); -- workaround cause 48277 dont deal damage
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48246','1','0');
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('47593','1','28351'); -- freezing cloud
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('47563','1','2300001'); -- freezing cloud
-- Statis orb (gortok palehoof fight)
UPDATE creature_template SET flags_extra=2 WHERE entry=26688; -- Statis orb
-- SQL for Skadi the Ruthless & King Ymiron Utgarde Pinnacle
-- Flame Breath Trigger (Skadi) 28351
-- Ymirjar Warrior (26690, 30822)
-- Ymirjar Witch Doctor (26691, 30823)
-- Ymirjar Harpooner (26692, 30819)
-- AVENGING_SPIRIT(27386,30756)
UPDATE creature_template SET equipment_id=1732 WHERE entry=30807; -- Skadi the Ruthless  hero

UPDATE creature_template SET faction_A = 21, faction_H = 21 WHERE entry IN (26690,30822,26692,30819,26691,30823);
UPDATE creature_template SET VehicleId=50, ScriptName= 'boss_grauf' WHERE entry=26893; -- Grauf
UPDATE creature_template SET VehicleId=50 WHERE entry=30775; -- Grauf hero
UPDATE creature_template SET mindmg=404, maxdmg=564, dmg_multiplier=7.5, AIName= 'EventAI' WHERE entry=26690; -- Ymirjar Warrior (26690)
UPDATE creature_template SET mindmg=464, maxdmg=604, dmg_multiplier=13 WHERE entry=30822; -- Ymirjar Warrior H(30822)
UPDATE creature_template SET mindmg=300, maxdmg=404, dmg_multiplier=7.5, AIName= 'EventAI' WHERE entry=26691; -- Ymirjar Witch Doctor (26691)
UPDATE creature_template SET mindmg=304, maxdmg=404, dmg_multiplier=13 WHERE entry=30823; -- Ymirjar Witch Doctor H(30823)
UPDATE creature_template SET mindmg=350, maxdmg=504, dmg_multiplier=7.5, AIName= 'EventAI' WHERE entry=26692; -- Ymirjar Harpooner (26692)
UPDATE creature_template SET mindmg=404, maxdmg=554, dmg_multiplier=13 WHERE entry=30819; -- Ymirjar Harpooner H(30819)
UPDATE creature_template SET faction_A = 14, faction_H = 14,mindmg=100, maxdmg=200, dmg_multiplier=7.5, AIName= 'EventAI' WHERE entry=27386; -- AVENGING_SPIRIT
UPDATE creature_template SET faction_A = 14, faction_H = 14, mindmg=100, maxdmg=200, dmg_multiplier=13 WHERE entry=30756; -- AVENGING_SPIRIT H
UPDATE creature_template SET faction_A = 14, faction_H = 14, flags_extra=flags_extra&~130 WHERE entry IN (27339,30808); -- Spirit Fount
-- King Bjorn (1),King Haldor (1),King Ranulf (1),King Tor (1)
UPDATE creature_template SET faction_A = 14, faction_H = 14, flags_extra=flags_extra|2 WHERE entry IN (30780,30782,30784,30786);
UPDATE creature_template SET equipment_id=653 WHERE entry=30788; -- King Ymiron H

DELETE FROM `creature_ai_scripts` WHERE id in (2669001,2669002,2669101,2669102,2669103,2669104,2669201,2669202,2669203,2738601);
insert into `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) values

-- Ymirjar Warrior (26690, 30822)
(2669001,26690,0,0,100,7,6000,9000,12000,17000,11,48639,1,0,0,0,0,0,0,0,0,0, 'Ymirjar Warrior - Cast Hamstring'),
(2669002,26690,0,0,100,7,6000,9000,12000,17000,11,48640,1,0,0,0,0,0,0,0,0,0, 'Ymirjar Warrior - Cast Strike'),
-- Ymirjar Witch Doctor (26691, 30823)
(2669101,26691,0,0,100,3,5000,8000,5000,8000,11,49084,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Witch Doctor (normal) - Cast Shadow Bolt'),
(2669102,26691,0,0,100,3,1000,5000,10000,15000,11,49089,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Witch Doctor (normal) - Cast Shrink'),
(2669103,26691,0,0,100,5,5000,8000,5000,8000,11,59246,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Witch Doctor (heroic) - Cast Shadow Bolt'),
(2669104,26691,0,0,100,5,1000,5000,10000,15000,11,59247,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Witch Doctor (heroic) - Cast Shrink'),
-- Ymirjar Harpooner (26692, 30819)
(2669201,26692,0,0,100,7,1000,3000,6000,10000,11,49092,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Harpooner - Cast Net'),
(2669202,26692,0,0,100,7,3000,5000,3000,5000,11,49091,4,0,0,0,0,0,0,0,0,0, 'Ymirjar Harpooner - Cast Throw'),
(2669203,26692,6,0,100,6,0,0,0,0,11,56790,6,16,0,0,0,0,0,0,0,0, 'Ymirjar Harpooner - Cast Create Harpoon'),
-- AVENGING_SPIRIT
(2738601,27386,0,0,100,7,3000,5000,3000,5000,11,48584,4,0,0,0,0,0,0,0,0,0, 'AVENGING_SPIRIT - Cast Wither');
-- Harpoon launcher
UPDATE gameobject_template SET ScriptName= 'go_harpoon' WHERE entry IN (192175,192176,192177);
-- Flame Breath Trigger (Skadi) 28351
DELETE FROM creature_template WHERE entry=2300001;
insert into `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) values
('2300001','0','0','0','0','0','18783','16925','0','0','Flame Breath Trigger (Skadi)','','','0','80','80','2','14','14','0','1','1.14286','1','0','422','586','0','642','1','2000','0','1','33554432','0','0','0','0','0','0','345','509','103','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','0','3','1.35','1','1','0','0','0','0','0','0','0','0','1','0','0','130','','11403');
UPDATE creature SET id=2300001 WHERE guid IN (126178,126179,126180,126181,126182,126183,126184,126185,126186,126187,126227,126228,126229,126230,126231,126232,126233,126234,126235,126236,126237,126190,126191,126192,126193,126194,126195,126196,126197,126198,126199,126173,126174,126176,126210,126211,126212,126213);
-- (2835101,28351,8,0,100,2,47563,-1,1,2,11,47579,0,0,0,0,0,0,0,0,0,0, 'Flame Breath Trigger (Skadi)  - Cast Freezing Cloud'),
-- (2835102,28351,8,0,100,4,47563,-1,1,2,11,60020,0,0,0,0,0,0,0,0,0,0, 'Flame Breath Trigger (Skadi)  - Cast Freezing Cloud hero'),
DELETE FROM spell_linked_spell WHERE spell_trigger IN (47563,47593);
INSERT INTO spell_linked_spell (spell_trigger,spell_effect,type,comment) VALUES
(47563,47579,1, 'Freezing Cloud'),
(47593,47579,1, 'Freezing Cloud');
DELETE FROM spelldifficulty_dbc WHERE spellid0=47579 AND spellid1=60020;
INSERT INTO spelldifficulty_dbc (id,spellid0,spellid1) VALUES (23001,47579,60020);

-- -1 575 000 UTGARDE PINNACLE
DELETE FROM script_texts WHERE entry BETWEEN -1575040 AND -1575000;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1575000,'My liege! I have done as you asked, and now beseech you for your blessing!',13856,1,0,0,'svala SAY_INTRO_1'),
(-1575001,'Your sacrifice is a testament to your obedience. Indeed you are worthy of this charge. Arise, and forever be known as Svala Sorrowgrave!',14732,1,0,0,'svala SAY_INTRO_2_ARTHAS'),
(-1575002,'The sensation is... beyond my imagining. I am yours to command, my king.',13857,1,0,0,'svala SAY_INTRO_3'),
(-1575003,'Your first test awaits you. Destroy our uninvited guests.',14733,1,0,0,'svala SAY_INTRO_4_ARTHAS'),
(-1575004,'I will be happy to slaughter them in your name! Come, enemies of the Scourge! I will show you the might of the Lich King!',13858,1,0,0,'svala SAY_INTRO_5'),
(-1575005,'I will vanquish your soul!',13842,1,0,0,'svala SAY_AGGRO'),
(-1575006,'You were a fool to challenge the power of the Lich King!',13845,1,0,0,'svala SAY_SLAY_1'),
(-1575007,'Your will is done, my king.',13847,1,0,0,'svala SAY_SLAY_2'),
(-1575008,'Another soul for my master.',13848,1,0,0,'svala SAY_SLAY_3'),
(-1575009,'Your death approaches.',13850,1,0,0,'svala SAY_SACRIFICE_1'),
(-1575010,'Go now to my master.',13851,1,0,0,'svala SAY_SACRIFICE_2'),
(-1575011,'Your end is inevitable.',13852,1,0,0,'svala SAY_SACRIFICE_3'),
(-1575012,'Yor-guul mak!',13853,1,0,0,'svala SAY_SACRIFICE_4'),
(-1575013,'Any last words?',13854,1,0,0,'svala SAY_SACRIFICE_5'),
(-1575014,'Nooo! I did not come this far... to...',13855,1,0,0,'svala SAY_DEATH'),

(-1575015,'What this place? I will destroy you!',13464,1,0,0,'gortok SAY_AGGRO'),
(-1575016,'You die! That what master wants!',13465,1,0,0,'gortok SAY_SLAY_1'),
(-1575017,'An easy task!',13466,1,0,0,'gortok SAY_SLAY_2'),
(-1575018,' ',13467,1,0,0,'gortok SAY_DEATH'),

(-1575019,'What mongrels dare intrude here? Look alive, my brothers! A feast for the one that brings me their heads!',13497,1,0,0,'skadi SAY_AGGRO'),
(-1575020,'Sear them to the bone!',13498,1,0,0,'skadi SAY_DRAKEBREATH_1'),
(-1575021,'Go now! Leave nothing but ash in your wake!',13499,1,0,0,'skadi SAY_DRAKEBREATH_2'),
(-1575022,'Cleanse our sacred halls with flame!',13500,1,0,0,'skadi SAY_DRAKEBREATH_3'),
(-1575023,'I ask for ... to kill them, yet all I get is feeble whelps! By Ye.. SLAUGHTER THEM!',13501,1,0,0,'skadi SAY_DRAKE_HARPOON_1'),
(-1575024,'If one more harpoon touches my drake I\'ll flae my miserable heins.',13502,1,0,0,'skadi SAY_DRAKE_HARPOON_2'),
(-1575025,'Mjor Na Ul Kaval!',13503,1,0,0,'skadi SAY_KILL_1'),
(-1575026,'Not so brash now, are you?',13504,1,0,0,'skadi SAY_KILL_2'),
(-1575027,'I\'ll mount your skull from the highest tower!',13505,1,0,0,'skadi SAY_KILL_3'),
(-1575028,'ARGH! You call that... an attack? I\'ll... show... aghhhh...',13506,1,0,0,'skadi SAY_DEATH'),
(-1575029,'You motherless knaves! Your corpses will make fine morsels for my new drake!',13507,1,0,0,'skadi SAY_DRAKE_DEATH'),
(-1575030,'%s is within range of the harpoon launchers!',0,3,0,0,'skadi EMOTE_HARPOON_RANGE'),

(-1575031,'You invade my home and then dare to challenge me? I will tear the hearts from your chests and offer them as gifts to the death god! Rualg nja gaborr!',13609,1,0,0,'ymiron SAY_AGGRO'),
(-1575032,'Bjorn of the Black Storm! Honor me now with your presence!',13610,1,0,0,'ymiron SAY_SUMMON_BJORN'),
(-1575033,'Haldor of the rocky cliffs, grant me your strength!',13611,1,0,0,'ymiron SAY_SUMMON_HALDOR'),
(-1575034,'Ranulf of the screaming abyss, snuff these maggots with darkest night!',13612,1,0,0,'ymiron SAY_SUMMON_RANULF'),
(-1575035,'Tor of the Brutal Siege! Bestow your might upon me!',13613,1,0,0,'ymiron SAY_SUMMON_TORGYN'),
(-1575036,'Your death is only the beginning!',13614,1,0,0,'ymiron SAY_SLAY_1'),
(-1575037,'You have failed your people!',13615,1,0,0,'ymiron SAY_SLAY_2'),
(-1575038,'There is a reason I am king!',13616,1,0,0,'ymiron SAY_SLAY_3'),
(-1575039,'Bleed no more!',13617,1,0,0,'ymiron SAY_SLAY_4'),
(-1575040,'What... awaits me... now?',13618,1,0,0,'ymiron SAY_DEATH');
