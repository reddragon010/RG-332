-- XP Eliminator Emotes
DELETE FROM `script_texts` WHERE `entry` IN (-1999991, -1999992, -1999993, -1999994);
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`, `type`, `comment`) VALUES ('-1999991', '%s plans a Stranglethorn Vale fishing trip.', '%s plant einen Angelausflug ins Schlingendorntal.', 2, 'XP Eliminator EMOTE 1');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`, `type`, `comment`) VALUES ('-1999992', '%s realizes he needs some Leggings of the Fang.', '%s erkennt, dass er die Gamaschen des Giftzahns benötigt.', 2, 'XP Eliminator EMOTE 2');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`, `type`, `comment`) VALUES ('-1999993', '%s bemoans the loss of his Nethercleft Leg Armor.', '%s betrauert den Verlust seiner Netherkluftbeinrüstung.', 2, 'XP Eliminator EMOTE 3');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc3`, `type`, `comment`) VALUES ('-1999994', '%s daydreams of Lucky Fishing Hats.', '%s träumt von Glücksangelhüten.', 2, 'XP Eliminator EMOTE 4');
