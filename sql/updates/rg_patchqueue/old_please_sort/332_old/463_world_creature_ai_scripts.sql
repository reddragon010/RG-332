DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28583';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28579';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28578';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28580';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28585';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28835';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28920';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='29240';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28582';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28836';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28837';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28581';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28826';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28547';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28961';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28965';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28838';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28584';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28585';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28965';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28581';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28547';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28580';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28826';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28835';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28920';
DELETE FROM `creature_ai_scripts` WHERE `creature_id`='28579';




UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28583';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28579';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28578';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28580';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28585';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28835';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28920';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='29240';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28582';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28582';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28836';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28837';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28581';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28826';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28547';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28961';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28965';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28838';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28584';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28585';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28965';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28581';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28547';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28580';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28826';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28835';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28920';
UPDATE `creature_template` SET `AIName`='EventAI' WHERE `entry`='28579';



INSERT INTO `creature_ai_scripts` VALUES (2858301, 28583, 0, 0, 100, 3, 5000, 8000, 12000, 15000, 11, 52531, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Blistering_Steamrager_Steam_Blast_Normal'),
(2858302, 28583, 0, 0, 100, 5, 5000, 8000, 12000, 15000, 11, 59141, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Blistering_Steamrager_Steam_Blast_Heroic'),
(2857901, 28579, 0, 0, 100, 3, 4000, 7000, 7000, 10000, 11, 52740, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Hurl_Weapon_Normal'),
(2857902, 28579, 0, 0, 100, 5, 4000, 7000, 7000, 10000, 11, 59259, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Hurl_Weapon_Heroic'),
(2857903, 28579, 2, 0, 100, 1, 30, 0, 120000, 130000, 11, 61369, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Enrage_At_30%'),
(2857801, 28578, 0, 0, 100, 1, 4000, 7000, 9000, 13000, 11, 42724, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Reaver_Cleave'),
(2857802, 28578, 0, 0, 100, 3, 9000, 12000, 15000, 18000, 11, 15655, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Reaver_Shield_Slam_Normal'),
(2857803, 28578, 0, 0, 100, 5, 9000, 12000, 15000, 18000, 11, 59142, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Reaver_Shield_Slam_Heroic'),
(2858001, 28580, 0, 0, 100, 3, 3500, 7000, 3500, 7000, 11, 16100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Shoot_Normal'),
(2858002, 28580, 0, 0, 100, 5, 3500, 7000, 3500, 7000, 11, 61515, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Shoot_Heroic'),
(2858003, 28580, 0, 0, 100, 3, 9000, 12000, 17000, 20000, 11, 52754, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Impact_Shoot_Normal'),
(2858004, 28580, 0, 0, 100, 5, 9000, 12000, 17000, 20000, 11, 59148, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Impact_Shoot_Heroic'),
(2858005, 28580, 0, 0, 100, 3, 14000, 18000, 25000, 30000, 11, 52755, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Impact_Multi_Shoot_Normal'),
(2858006, 28580, 0, 0, 100, 5, 14000, 18000, 25000, 30000, 11, 59147, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Impact_Multi_Shoot_Heroic'),
(2858007, 28580, 3, 0, 100, 1, 0, 5000, 10000, 13000, 11, 61507, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Disengage'),
(2858501, 28585, 0, 0, 100, 3, 4000, 7000, 12000, 15000, 11, 22424, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Slag_Blast_Wave_Normal'),
(2858504, 28585, 0, 0, 100, 3, 9000, 12000, 35000, 38000, 11, 61509, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Slag_Melt_Armor_Normal'),
(2858503, 28585, 0, 0, 100, 5, 9000, 12000, 35000, 38000, 11, 61510, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Slag_Melt_Armor_Heroic'),
(2883501, 28835, 0, 3, 100, 3, 4000, 8000, 9000, 14000, 11, 53068, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Rune_Punch_Normal'),
(2883502, 28835, 0, 3, 100, 5, 4000, 8000, 9000, 14000, 11, 59151, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Rune_Punch_Heroic'),
(2883503, 28835, 0, 0, 100, 3, 4000, 7000, 12000, 15000, 11, 53167, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Forked_Lightning_Normal'),
(2883504, 28835, 0, 0, 100, 5, 4000, 7000, 12000, 15000, 11, 59152, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Forked_Lightning_Heroic'),
(2883505, 28835, 0, 0, 100, 3, 10000, 15000, 17000, 20000, 11, 61596, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Runic_Focus_Normal'),
(2883506, 28835, 0, 0, 100, 5, 10000, 15000, 17000, 20000, 11, 61579, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Runic_Focus_Heroic'),
(2892001, 28920, 0, 3, 100, 1, 4000, 7000, 9000, 12000, 11, 32315, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Soul_Strike'),
(2892002, 28920, 0, 0, 100, 3, 5000, 10000, 12000, 15000, 11, 53072, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Stormbolt_Normal'),
(2892003, 28920, 0, 0, 100, 5, 5000, 10000, 12000, 15000, 11, 59155, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Stormbolt_Heroic'),
(2892004, 28920, 0, 3, 100, 3, 9000, 14000, 17000, 20000, 11, 53071, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Thunderstorm_Normal'),
(2892005, 28920, 0, 3, 100, 5, 9000, 14000, 17000, 20000, 11, 59154, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Thunderstorm_Heroic'),
(2924003, 29240, 0, 0, 100, 1, 5000, 10000, 7000, 10000, 11, 59085, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Lieutenant_Arc_Weld'),
(2924002, 29240, 14, 0, 100, 3, 6000, 25, 27000, 30000, 11, 52774, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Lieutenant_Renew_Steel_Normal'),
(2924001, 29240, 14, 0, 100, 5, 15000, 25, 22000, 25000, 11, 59160, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Lieutenant_Renew_Steel_Heroic'),
(2858202, 28582, 14, 0, 100, 3, 2000, 25, 27000, 30000, 11, 52774, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Mender_Renew_Steel_Normal'),
(2858201, 28582, 14, 0, 100, 5, 30000, 25, 22000, 25000, 11, 59160, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Mender_Renew_Steel_Heroic'),
(2858203, 28582, 0, 0, 100, 1, 4000, 7000, 9000, 12000, 11, 52773, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Mender_Hammer_Blow'),
(2883603, 28836, 15, 0, 100, 1, 0, 15, 15000, 18000, 11, 53048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Runeshaper_Startling_Roar'),
(2883602, 28836, 0, 0, 100, 3, 7000, 11000, 19000, 23000, 11, 53049, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Runeshaper_Charged_Flurry_Normal'),
(2883601, 28836, 0, 0, 100, 5, 7000, 11000, 19000, 23000, 11, 61581, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Runeshaper_Charged_Flurry_Heroic'),
(2883705, 28837, 0, 0, 100, 3, 5000, 10000, 19000, 23000, 11, 53045, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Sentinel_Sleep_Normal'),
(2883704, 28837, 0, 0, 100, 5, 5000, 10000, 19000, 23000, 11, 59165, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Sentinel_Sleep_Heroic'),
(2883703, 28837, 14, 0, 100, 3, 10000, 25, 17000, 20000, 11, 34423, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Sentinel_Renew_Normal'),
(2883702, 28837, 14, 0, 100, 5, 15000, 25, 17000, 20000, 11, 37978, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Sentinel_Renew_Heroic'),
(2883701, 28837, 2, 0, 100, 1, 30, 0, 27000, 30000, 11, 53047, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Sentinel_Storming_Bellow'),
(2858103, 28581, 0, 0, 100, 1, 9000, 12000, 14000, 17000, 11, 59085, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Arc_Weld'),
(2858102, 28581, 0, 0, 100, 3, 4000, 7000, 9000, 12000, 11, 52778, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Welding_Beam_Normal'),
(2858101, 28581, 0, 0, 100, 5, 4000, 7000, 9000, 12000, 11, 59166, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Welding_Beam_Heroic'),
(2882604, 28826, 0, 0, 100, 3, 10000, 13000, 12000, 15000, 11, 53043, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Electro_Shock_Normal'),
(2882603, 28826, 0, 0, 100, 5, 10000, 13000, 12000, 15000, 11, 59168, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Electro_Shock_Heroic'),
(2882602, 28826, 0, 0, 100, 3, 4000, 7000, 14000, 17000, 11, 52905, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Thunderbolt_Nomal'),
(2882601, 28826, 0, 0, 100, 5, 4000, 7000, 14000, 17000, 11, 59167, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Thunderbolt_Heroic'),
(2854703, 28547, 0, 0, 100, 1, 9000, 12000, 18000, 21000, 11, 60236, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Cyclone'),
(2854702, 28547, 0, 0, 100, 3, 3500, 7000, 3500, 7000, 11, 53044, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Lightning_Bolt_Normal'),
(2854701, 28547, 0, 0, 100, 5, 3500, 7000, 3500, 7000, 11, 59169, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Lightning_Bolt_Heroic'),
(2896105, 28961, 2, 0, 100, 3, 30, 0, 12000, 15000, 11, 52891, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Siegebreaker_Blade_Turning'),
(2896104, 28961, 2, 0, 100, 5, 30, 0, 12000, 15000, 11, 59173, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Siegebreaker_Blade_Turning'),
(2896103, 28961, 0, 0, 100, 1, 4000, 7000, 9000, 12000, 11, 52890, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Siegebreaker_Penetrating_Strike'),
(2896102, 28961, 0, 0, 100, 1, 12000, 15000, 29000, 33000, 11, 19134, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Siegebreaker_Frightenning_Shout'),
(2896101, 28961, 0, 0, 100, 1, 20000, 23000, 22000, 25000, 11, 23600, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Siegebreaker_Piercing_Howl'),
(2896506, 28965, 0, 0, 100, 3, 3500, 7000, 7000, 10000, 11, 52904, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Throw_Normal'),
(2896505, 28965, 0, 0, 100, 5, 3500, 7000, 7000, 10000, 11, 59179, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Throw_Heroic'),
(2896504, 28965, 13, 0, 100, 3, 17000, 21000, 0, 0, 11, 52885, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Deadly_Throw_Normal'),
(2896503, 28965, 13, 0, 100, 5, 17000, 21000, 0, 0, 11, 59180, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Deadly_Throw_Heroic'),
(2896502, 28965, 2, 3, 100, 3, 50, 0, 10000, 13000, 11, 52879, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Deflection_Normal'),
(2896501, 28965, 2, 3, 100, 5, 50, 0, 10000, 13000, 11, 59180, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Deflection_Heroic'),
(2883803, 28838, 4, 0, 100, 1, 0, 0, 0, 0, 11, 58619, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Vanguard_Charge'),
(2883802, 28838, 0, 0, 100, 3, 4000, 7000, 12000, 15000, 11, 59178, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Vanguard_Poison_Tipped_Spear_Normal'),
(2883801, 28838, 0, 0, 100, 5, 4000, 7000, 12000, 15000, 11, 53059, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Vanguard_Poison_Tipped_Spear_Heroic'),
(2858403, 28584, 0, 0, 100, 3, 30, 0, 17000, 21000, 11, 52624, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Unbound_Firestorm_Afterburn'),
(2858404, 28584, 2, 0, 100, 5, 30, 0, 17000, 21000, 11, 59183, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Unbound_Firestorm_Afterburn'),
(2858402, 28584, 0, 0, 100, 3, 4000, 7000, 9000, 12000, 11, 53788, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Unbound_Firestorm_Lava_Burst'),
(2858401, 28584, 0, 0, 100, 5, 4000, 7000, 9000, 12000, 11, 59182, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 'Unbound_Firestorm_Lava_Burst'),
(2858502, 28585, 0, 0, 100, 5, 4000, 7000, 12000, 15000, 11, 23113, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Slag_Blast_Wave_Heroic'),
(2896508, 28965, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Start_Combat_Movement_Below_5_Yards'),
(2896509, 28965, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2896510, 28965, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2896511, 28965, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_Set Phase_1_on_Aggro'),
(2896507, 28965, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Titanium_Thunderer_On_Evade_set_Phase_to_0'),
(2858108, 28581, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Start_Combat_Movement_Below_5_Yards'),
(2858104, 28581, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2858105, 28581, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2858106, 28581, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_Set Phase_1_on_Aggro'),
(2858107, 28581, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Tactician_On_Evade_set_Phase_to_0'),
(2854708, 28547, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Start_Combat_Movement_Below_5_Yards'),
(2854704, 28547, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2854705, 28547, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2854706, 28547, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_Set Phase_1_on_Aggro'),
(2854707, 28547, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Storming_Vortex_On_Evade_set_Phase_to_0'),
(2858008, 28580, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Start_Combat_Movement_Below_5_Yards'),
(2858009, 28580, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2858010, 28580, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2858011, 28580, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_Set Phase_1_on_Aggro'),
(2858012, 28580, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Skycaller_On_Evade_set_Phase_to_0'),
(2882607, 28826, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2882606, 28826, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2882605, 28826, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Start_Combat_Movement_Below_5_Yards'),
(2882608, 28826, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_Set Phase_1_on_Aggro'),
(2882609, 28826, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormfury_Revenant_On_Evade_set_Phase_to_0'),
(2883510, 28835, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Start_Combat_Movement_Below_5_Yards'),
(2883511, 28835, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2883507, 28835, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2883508, 28835, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_Set Phase_1_on_Aggro'),
(2883509, 28835, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Construct_On_Evade_set_Phase_to_0'),
(2892010, 28920, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Start_Combat_Movement_Below_5_Yards'),
(2892006, 28920, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2892007, 28920, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2892008, 28920, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_Set Phase_1_on_Aggro'),
(2892009, 28920, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Stormforged_Giant_On_Evade_set_Phase_to_0'),
(2857904, 28579, 9, 5, 100, 0, 0, 5, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Start_Combat_Movement_Below_5_Yards'),
(2857906, 28579, 9, 5, 100, 0, 5, 15, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Prevent_Combat_Movement_at_15_Yards_(Phase_1)'),
(2857907, 28579, 9, 5, 100, 0, 35, 80, 0, 0, 21, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Start_Combat_Movement_at_35_Yards_(Phase_1)'),
(2857908, 28579, 4, 0, 100, 0, 0, 0, 0, 0, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_Set Phase_1_on_Aggro'),
(2857905, 28579, 7, 0, 100, 0, 0, 0, 0, 0, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Hardened_Steel_Berserker_On_Evade_set_Phase_to_0');