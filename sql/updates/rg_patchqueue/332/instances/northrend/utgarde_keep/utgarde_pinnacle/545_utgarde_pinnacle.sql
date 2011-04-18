-- Svala Sorrowgrave, Svala Sorrowgrave H, ritual channeler, ritual channeler hero, Ritual Target , Ritual Target H faction 
UPDATE creature_template SET faction_A=14, faction_H=14 WHERE entry IN (26668,30810,27281,30804,27327,30805);
-- flame brazier, flame brazier hero, Ritual Target , Ritual Target H
UPDATE creature_template SET faction_A=35, faction_H=35, flags_extra=flags_extra|2&~128 WHERE entry IN (27273,30771,27327,30805); 
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
-- ritual strike target
DELETE FROM spell_script_target WHERE ENTRY IN (48277,59930);
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48277','1','0');
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('48277','1','26555');
insert into `spell_script_target` (`entry`, `type`, `targetEntry`) values('59930','1','26555'); -- workaround cause 48277 dont deal damage
-- SQL for Skadi the Ruthless & King Ymiron Utgarde Pinnacle
-- Ymirjar Warrior (26690, 30822)
-- Ymirjar Witch Doctor (26691, 30823)
-- Ymirjar Harpooner (26692, 30819)
-- AVENGING_SPIRIT(27386,30756)
UPDATE creature_template SET faction_A = 21, faction_H = 21 WHERE entry IN (26690,30822,26692,30819,26691,30823);

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
