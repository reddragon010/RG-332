-- Dark Ranger Marrah Fixxed vor Burg Utgarde
DELETE FROM `creature` WHERE `id`=24137;
INSERT INTO `creature` VALUES 
(2600061, 24137, 571, 1, 1, 24202, 0, 1220.327, -4853.437, 41.249, 4.348, 180, 0, 0, 4389, 0, 0, 0);

-- Eiskrone/Schiff Quest-Geber alli
UPDATE `creature` SET `position_x`=7269.00, `position_y`=1511.72, `position_z`=320.91, `orientation`=4.58 WHERE `guid`=122954;
UPDATE `creature` SET `position_x`=7276.63, `position_y`=1513.199, `position_z`=319.36, `orientation`=3.4 WHERE `guid`=121174;
UPDATE `creature` SET `position_x`=7263.71, `position_y`=1515.25, `position_z`=321.76, `orientation`=6.16 WHERE `guid`=121614;

-- Eiskrone/Schiff Quest-Geber HORDE
DELETE FROM `creature` WHERE `guid` IN (5900006);
INSERT INTO `creature` VALUES 
(5900006, 30824, 571, 1, 1, 17836, 0, 7503.02, 1810.37, 355.66, 4.65, 30, 0, 0, 121368, 0, 0, 0);
UPDATE `creature` SET `position_x`=7493.88, `position_y`=1804.27, `position_z`=361.22, `orientation`=0.09 WHERE `guid`=122541;
UPDATE `creature` SET `position_x`=7493.198, `position_y`=1797.07, `position_z`=362.44, `orientation`=6.14 WHERE `guid`=121606;
