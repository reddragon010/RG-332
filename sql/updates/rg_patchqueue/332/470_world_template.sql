-- 0000401 Ein Desaster konstruieren --
DELETE FROM `script_waypoint` WHERE `entry`= 28787;
DELETE FROM `creature_template` WHERE `entry`= 28787;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(28787, 0, 0, 0, 0, 0, 25681, 0, 0, 0, 'Engineer Helice', '', '', 0, 76, 76, 2, 35, 35, 2, 1, 1, 0, 352, 499, 0, 408, 1, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 302, 449, 57, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 57, 0, 0, 'npc_engineer_helice', 11159);
DELETE FROM `script_waypoint` WHERE `entry`= 28787;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(28787, 1, 5917.36, 5377.24, -98.8972, 0, NULL),
(28787, 2, 5926.56, 5372.97, -98.8947, 0, NULL),
(28787, 3, 5928.18, 5377.22, -99.029, 0, NULL),
(28787, 4, 5907, 5389.82, -106.31, 0, NULL),
(28787, 5, 5901.52, 5407.58, -95.9815, 0, NULL),
(28787, 6, 5902.07, 5424.09, -93.8154, 0, NULL),
(28787, 7, 5907.25, 5441.99, -90.9601, 0, NULL),
(28787, 8, 5912.61, 5458.64, -89.5963, 0, NULL),
(28787, 9, 5918.34, 5479.97, -85.3212, 0, NULL),
(28787, 10, 5910.45, 5503.78, -79.6172, 0, NULL),
(28787, 11, 5906.15, 5525.42, -79.2766, 0, NULL),
(28787, 12, 5898.66, 5545.55, -80.3461, 0, NULL),
(28787, 13, 5888.08, 5567.85, -79.0892, 0, NULL),
(28787, 14, 5877.11, 5580.17, -76.5766, 0, NULL),
(28787, 15, 5861.62, 5592.22, -72.5486, 0, NULL),
(28787, 16, 5845.94, 5604.4, -69.9079, 0, NULL),
(28787, 17, 5826.83, 5617.83, -70.3254, 0, NULL),
(28787, 18, 5806.7, 5626.89, -69.567, 0, NULL),
(28787, 19, 5785.3, 5636.51, -70.5163, 0, NULL),
(28787, 20, 5764.58, 5645.84, -74.3202, 0, NULL),
(28787, 21, 5744.45, 5654.9, -75.3451, 0, NULL),
(28787, 22, 5715.07, 5671.86, -79.7276, 0, NULL),
(28787, 23, 5696.48, 5683.08, -78.146, 0, NULL),
(28787, 24, 5681.29, 5697.72, -80.764, 0, NULL),
(28787, 25, 5652.1, 5725.21, -82.3119, 0, NULL),
(28787, 26, 5629.36, 5744.3, -74.2628, 0, NULL),
(28787, 27, 5611.22, 5759.53, -71.2035, 0, NULL),
(28787, 28, 5591.31, 5762.07, -71.6436, 0, NULL),
(28787, 29, 5584.75, 5750.53, -72.0055, 0, NULL);

