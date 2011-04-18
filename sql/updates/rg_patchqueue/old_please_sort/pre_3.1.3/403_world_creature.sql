 
-- 0000534: Nordend - Mr. Floppys gef�hrliches Abenteuer --
DELETE FROM `creature_template` WHERE `entry`= 26588;
INSERT INTO `creature_template` (`entry`, `heroic_entry`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `unk16`, `unk17`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`) VALUES
(26588, 0, 0, 0, 23949, 0, 0, 0, 'Emily', '', '', 5, 5, 102, 102, 0, 0, 0, 35, 35, 2, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 110, 1, 0, 0, 0, 'npc_emily');
DELETE FROM `script_waypoint` WHERE `entry`=26588;
INSERT INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`) VALUES
(26588, 1, 4326.62, -3691.65, 263.841),
(26588, 2, 4332.73, -3688.22, 263.897),
(26588, 3, 4336.76, -3685.96, 261.221),
(26588, 4, 4340.91, -3683.62, 257.507),
(26588, 5, 4347.42, -3685.43, 256.738),
(26588, 6, 4349.77, -3689.56, 256.43),
(26588, 7, 4353.28, -3695.71, 255.29),
(26588, 8, 4354.68, -3702.71, 253.194),
(26588, 9, 4356.52, -3711.9, 249.051),
(26588, 10, 4360.22, -3730.37, 241.012),
(26588, 11, 4363.47, -3746.63, 234.294),
(26588, 12, 4366.27, -3760.57, 228.565),
(26588, 13, 4374.51, -3779.8, 219.709),
(26588, 14, 4384.8, -3798.11, 211.4),
(26588, 15, 4393.99, -3814.47, 207.887),
(26588, 16, 4398.65, -3822.77, 207.636),
(26588, 17, 4402.14, -3834, 205.669),
(26588, 18, 4407.24, -3847.03, 201.115),
(26588, 19, 4413.07, -3857.25, 197.867),
(26588, 20, 4420.04, -3869.47, 194.748),
(26588, 21, 4427.56, -3882.67, 192.235),
(26588, 22, 4433.35, -3892.82, 190.614),
(26588, 23, 4439.17, -3903.04, 189.854),
(26588, 24, 4447.23, -3911.9, 189.478),
(26588, 25, 4458.34, -3924.12, 189.286),
(26588, 26, 4469.41, -3936.29, 189.354),
(26588, 27, 4477.37, -3945.04, 189.476),
(26588, 28, 4479.53, -3961.35, 189.118),
(26588, 29, 4478.43, -3973.27, 187.592),
(26588, 30, 4477.14, -3987.42, 186.134),
(26588, 31, 4481.63, -4003.61, 184.878),
(26588, 32, 4485.32, -4022.33, 180.011),
(26588, 33, 4492.19, -4042.4, 177.461),
(26588, 34, 4497.53, -4058.03, 175.499),
(26588, 35, 4490.11, -4082.69, 173.932),
(26588, 36, 4494.84, -4095.87, 173.495),
(26588, 37, 4498.97, -4107.33, 172.139),
(26588, 38, 4506.13, -4122.08, 172.06),
(26588, 39, 4512.35, -4134.78, 172.006),
(26588, 40, 4527.93, -4154.77, 172.511),
(26588, 41, 4535.37, -4169.41, 173.445),
(26588, 42, 4537.52, -4187.9, 173.452),
(26588, 43, 4539.93, -4208.55, 170.881),
(26588, 44, 4542.78, -4220.14, 170.518),
(26588, 45, 4547.78, -4230.71, 170.492),
(26588, 46, 4562.98, -4225.2, 171.178),
(26588, 47, 4573.43, -4222.16, 173.908),
(26588, 48, 4585.85, -4218.76, 177.994),
(26588, 49, 4602.1, -4219.2, 178.654);

-- Fixed Knappe Walther --
DELETE FROM `creature` WHERE `id`= 26371;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(3467907, 26371, 571, 1, 1, 0, 174, 4602.3, -4217.78, 178.655, 3.46727, 25, 0, 0, 42, 0, 0, 0);
