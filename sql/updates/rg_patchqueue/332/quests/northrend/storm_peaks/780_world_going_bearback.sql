-- QuestFix going Bearback

-- Script verpassen
UPDATE `creature_template` SET `ScriptName` = 'npc_niffelem_frost_giant' WHERE `entry` in(29351, 29358);

-- Dem Bären die Spells verpassen
UPDATE `creature_template` SET `spell1` = '54897', `spell2` = '54907', `VehicleId` = '308' WHERE `entry` =29602;

-- Riding start spell
DELETE FROM npc_spellclick_spells WHERE npc_entry in (29598);
INSERT INTO npc_spellclick_spells VALUES (29598, 54768, 12851, 1, 12851, 1,0,0,0);
-- INSERT INTO npc_spellclick_spells VALUES (29598, 54908, 12851, 1, 12851, 1,0,0,0);
-- INSERT INTO npc_spellclick_spells VALUES (29598, 54788, 12851, 1, 12851, 1,0,0,0);
-- INSERT INTO npc_spellclick_spells VALUES (29598, 61169, 12851, 1, 12851, 1,0,0,0);