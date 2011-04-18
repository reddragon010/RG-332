-- removed missing model of Boss Felmyst
DELETE FROM `creature_template` WHERE `entry`=25038;
INSERT INTO `creature_template` VALUES(25038, 0, 0, 0, 22838, 0, 0, 0, 'Felmyst', '', '', 73, 73, 4900000, 4900000, 3387, 3387, 5500, 14, 14, 0, 1, 1, 3, 12113, 14212, 0, 6075, 1, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2250000, 2750000, '', 0, 1, 807.8, 1, 0, 0, 0, 0, 0, 0, 0, 222, 1, 0, 653213695, 1, 'boss_felmyst');
