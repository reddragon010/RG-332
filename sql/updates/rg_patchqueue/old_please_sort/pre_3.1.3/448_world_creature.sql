-- Enternen von Händlern, die "tödliches" s5 verkaufen, da zu wenig kosten.
-- Mit 3.2 könnte wiedr eingefügt werden ;)
DELETE FROM `creature` WHERE `Id` IN (24670,29539,24520,29540,32362,33916);
DELETE FROM `creature` WHERE `Id` =26045;
INSERT INTO `creature` VALUES 
-- Bezwingt den Sturm
(2600043, 26045, 571, 1, 1, 14516, 0, 3401.93, 4133.83, 18.06, 5.6, 100, 0, 0, 9291, 3000, 0, 0);