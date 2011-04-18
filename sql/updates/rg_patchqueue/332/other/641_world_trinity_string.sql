-- Texte fuer VIP Code NPCs
DELETE FROM `trinity_string` WHERE `entry` IN (100001, 100002, 100003, 100004, 100005);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (100005, 'You didn\'t enter a code.', NULL, NULL, 'Du hast noch keinen Code eingegeben.', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (100004, 'You already used your code.', NULL, NULL, 'Du hast deinen Code bereits benutzt.', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (100003, 'The entered code isn\'t valid oder doesn\'t exists.', NULL, NULL, 'Der eingegebene Code ist ungültig oder existiert nicht.', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (100002, 'I changed my mind.', NULL, NULL, 'Ich habe es mir anders überlegt.', NULL, NULL, NULL, NULL, NULL);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES (100001, 'I want to enter a Rising Gods Premium-Code.', NULL, NULL, 'Ich möchte einen Rising Gods Premium-Code einlösen.', NULL, NULL, NULL, NULL, NULL);


