-- S5.5 (t�dliches Gladi)
-- Brust
UPDATE `npc_vendor` SET `extendedcost`=2952 WHERE `item` IN (40991,40784,41080,40905,41920,41649,41086,40990,41951,40785,40786,41660,41997,41858,41315,41309);
-- Kopf
UPDATE `npc_vendor` SET `extendedcost`=2949 WHERE `item` IN (41018,40824,41150,40932,41914,41671,41156,41012,41945,40825,40823,41677,41992,41853,41326,41320);
-- H�nde
UPDATE `npc_vendor` SET `extendedcost`=2954 WHERE `item` IN (41006,40806,41136,40926,41939,41766,41142,41000,41970,40805,40804,41772,42016,41873,41292,41286);
-- Beine
UPDATE `npc_vendor` SET `extendedcost`=2953 WHERE `item` IN (41032,40845,41198,40938,41926,41654,41204,41026,41958,40846,40844,41666,42004,41863,41303,41297);
-- Schultern
UPDATE `npc_vendor` SET `extendedcost`=2948 WHERE `item` IN (41043,40863,41210,40962,41933,41682,41216,41037,41964,40864,40862,41714,42010,41868,41280,41274);

-- s5.5 sonstiges 33925
DELETE FROM `npc_vendor` WHERE `entry`=33925;
INSERT INTO `npc_vendor` VALUES
(33925, 42564, 0, 0, 2950),
(33925, 42559, 0, 0, 2950),
(33925, 42570, 0, 0, 2950),
(33925, 42531, 0, 0, 2950),
(33925, 42525, 0, 0, 2950),
(33925, 42537, 0, 0, 2950),
(33925, 42270, 0, 0, 2946),
(33925, 42265, 0, 0, 2946),
(33925, 42280, 0, 0, 2946),
(33925, 42290, 0, 0, 2946),
(33925, 42232, 0, 0, 2946),
(33925, 42227, 0, 0, 2946),
(33925, 42248, 0, 0, 2946),
(33925, 42255, 0, 0, 2946),
(33925, 42352, 0, 0, 2621),
(33925, 42275, 0, 0, 2945),
(33925, 42260, 0, 0, 2945),
(33925, 42285, 0, 0, 2945),
(33925, 42237, 0, 0, 2945),
(33925, 42208, 0, 0, 2945),
(33925, 42346, 0, 0, 2621),
(33925, 42242, 0, 0, 2945),
(33925, 42502, 0, 0, 2951),
(33925, 42519, 0, 0, 2951),
(33925, 42513, 0, 0, 2951),
(33925, 42450, 0, 0, 2951),
(33925, 42597, 0, 0, 2951),
(33925, 42607, 0, 0, 2951),
(33925, 42602, 0, 0, 2951),
(33925, 42583, 0, 0, 2951),
(33925, 42588, 0, 0, 2951),
(33925, 42614, 0, 0, 2951),
(33925, 42852, 0, 0, 2951),
(33925, 42620, 0, 0, 2951),
(33925, 42322, 0, 0, 2936),
(33925, 42332, 0, 0, 2936),
(33925, 42317, 0, 0, 2936),
(33925, 42327, 0, 0, 2936),
(33925, 42384, 0, 0, 2936),
(33925, 44420, 0, 0, 2936),
(33925, 42362, 0, 0, 2936),
(33925, 44419, 0, 0, 2936),
(33925, 42390, 0, 0, 2936),
(33925, 42485, 0, 0, 2936),
(33925, 42490, 0, 0, 2936),
(33925, 42495, 0, 0, 2936);