-- Die neue Seuche überarbeitung alter fix 
UPDATE `gameobject_template` SET `flags`=4 WHERE `entry`=186390;

-- 0000619: PVE - NORDEND - Laborarbeit
DELETE FROM `gameobject_template` WHERE `entry` IN (190459, 190462, 190473, 190478);
INSERT INTO `gameobject_template` VALUES
(190459, 3, 7918, 'Amberseed', '', 'Collecting', '', 0, 4, 0.4, 38346, 0, 0, 0, 0, 0, 1690, 190459, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(190462, 3, 228, 'Chilled Serpent Mucus', '', 'Collecting', '', 0, 4, 1, 38340, 0, 0, 0, 0, 0, 1690, 190462, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(190473, 3, 7924, 'Withered Batwing', '', 'Collecting', '', 0, 4, 0.02, 38339, 0, 0, 0, 0, 0, 1690, 190473, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(190478, 3, 6484, 'Muddy Mire Maggots', '', 'Collecting', '', 0, 4, 2, 0, 0, 0, 0, 0, 0, 1690, 190478, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
DELETE FROM `gameobject_loot_template` WHERE `entry` IN (190459, 190462, 190473, 190478);
INSERT INTO `gameobject_loot_template` VALUES
(190459, 38340, -100, 1, 0, 1, 1, 0, 0, 0),
(190462, 38346, -100, 1, 0, 1, 1, 0, 0, 0),
(190473, 38339, -100, 1, 0, 1, 1, 0, 0, 0),
(190478, 38386, -100, 1, 0, 1, 1, 0, 0, 0);