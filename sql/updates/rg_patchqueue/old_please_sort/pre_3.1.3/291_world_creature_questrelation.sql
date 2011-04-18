-- Remove wrong quests from npcs
DELETE FROM `creature_questrelation` WHERE `quest` IN (7362, 7368, 7367, 6846, 7361, 7364, 8369, 7366, 7365, 7363, 7366);
