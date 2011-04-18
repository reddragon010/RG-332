-- Acherus Teleporter (DK)

-- correct gameobjects
-- adding dummies
DELETE FROM `gameobject_template` WHERE `entry` IN ('191538', '191539', '2000001', '2000002');
-- startzone (609) upper
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (2000001, 6, 6699, 'RGTEMP Doodad_Nox_portal_purple_bossroom17', '', '', '', 114, 6553632, 0.7, 0, 0, 0, 0, 0, 0, 43, 0, 2, 54724, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
-- startzone (609) lower
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (2000002, 6, 6699, 'RGTEMP Doodad_Nox_portal_purple_bossroom01', '', '', '', 114, 6553632, 0.7, 0, 0, 0, 0, 0, 0, 43, 0, 2, 54700, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
-- normalzone (0) upper
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (191539, 6, 6699, 'Doodad_Nox_portal_purple_bossroom17', '', '', '', 114, 6553632, 0.7, 0, 0, 0, 0, 0, 0, 43, 0, 2, 54745, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');
-- normalzone (0) lower
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES (191538, 6, 6699, 'Doodad_Nox_portal_purple_bossroom01', '', '', '', 114, 6553632, 0.7, 0, 0, 0, 0, 0, 0, 43, 0, 2, 54742, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

-- spawn GOs
DELETE FROM `gameobject` WHERE `id` IN ('191538', '191539', '2000001', '2000002');
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(63186, 191539, 0, 1, 1, 2390.02, -5640.91, 377.094, 0.59341, 0, 0, 0.292372, 0.956305, 180, 100, 0),
(63187, 191538, 0, 1, 1, 2383.65, -5645.2, 420.773, 0.59341, 0, 0, 0.292372, 0.956305, 180, 100, 0),
(65893, 2000002, 609, 1, 1, 2390.02, -5640.91, 377.093, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(65895, 2000001, 609, 1, 1, 2383.65, -5645.2, 420.772, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66243, 2000002, 609, 1, 4, 2390.02, -5640.91, 377.093, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66244, 2000001, 609, 1, 4, 2383.65, -5645.2, 420.772, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66416, 2000002, 609, 1, 64, 2390.02, -5640.91, 377.093, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66417, 191539, 0, 1, 64, 2390.02, -5640.91, 377.094, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66418, 2000001, 609, 1, 64, 2383.65, -5645.2, 420.772, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0),
(66419, 191538, 0, 1, 64, 2383.65, -5645.2, 420.773, 0.59341, 0, 0, 0.292372, 0.956305, 180, 0, 0);

-- remove auraticker after adding aura
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN ('54725', '54746', '54699', '54744');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54699, -54700, 1, 'Archerus Teleporter Phase Hall -> Heart');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54725, -54724, 1, 'Archerus Teleporter Phases Heart->Hall');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54744, -54742, 1, 'Archerus Teleporter Hall -> Heart');
INSERT INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`) VALUES (54746, -54745, 1, 'Archerus Teleporter Heart->Hall');
