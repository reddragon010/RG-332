UPDATE `gameobject_template` SET `ScriptName` = 'go_barrel_of_papayas' WHERE `entry` =190639;
UPDATE `gameobject_template` SET `ScriptName` = 'go_barrel_of_bananas' WHERE `entry` =190638;
UPDATE `gameobject_template` SET `ScriptName` = 'go_barrel_of_oranges' WHERE `entry` =190637;
UPDATE `gameobject_template` SET `ScriptName` = 'go_brazier' WHERE `entry` =190636;
UPDATE `gameobject_template` SET `ScriptName` = 'go_pressure_valve' WHERE `entry` =190635;
UPDATE `creature_template` SET `ScriptName` = 'npc_tipsy' WHERE `entry` =28566;

INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
(28566, -1999990, 'Nein! Ihr habt es vermasselt!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'SAY_QFAIL tipsy'),
(28566, -1999989, 'Kommt, holt die Buddel!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_QEND tipsy'),
(28566, -1999988, 'Fast geschafft...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_END3 tipsy'),
(28566, -1999987, 'Durchhalten! Weiter!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_END2 tipsy'),
(28566, -1999986, 'Sehr gut! Weiter so!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'SAY_END1 tipsy'),
(28566, -1999985, 'Der Druck ist zu hoch! Öffnet das Druckventil!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, tipsy SAY_VALVE),
(28566, -1999984, 'Die Destille braucht Hitze! Entzündet die Kohlenpfanne!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'SAY_BRAZIER tipsy'),
(28566, -1999983, 'Gebt Orangen hinzu!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'tipsy SAY_ORANGE'),
(28566, -1999982, 'Gebt Bananen hinzu!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'tipsy SAY_BANANA'),
(28566, -1999981, 'Gebt Papayas hinzu!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'tipsy SAY_PAPAYA'),
(28566, -1999980, 'Lasst uns anfangen!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 3, 0, 0, 'npc tipsy begin quest');