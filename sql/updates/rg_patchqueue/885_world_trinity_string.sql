-- Gossip Texts for XP Eliminators
DELETE FROM `trinity_string` WHERE `entry` IN (100009, 100008, 100007, 100006);
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc3`) VALUES ('100009', 'Are you certain you wish to gain experience again?', 'Seid Ihr sicher, dass Ihr wieder beginnen möchtet, Erfahrungspunkte zu erhalten?');
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc3`) VALUES ('100008', 'I wish to start gaining experience again.', 'Ich wünsche, wieder Erfahrungspunkte zu erhalten.');
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc3`) VALUES ('100007', 'Are you certain you wish to stop gaining experience?', 'Seid Ihr sicher, dass Ihr aufhören möchtet, Erfahrungspunkte zu erhalten?');
INSERT INTO `trinity_string` (`entry`, `content_default`, `content_loc3`) VALUES ('100006', 'I no longer wish to gain experience.', 'Ich wünsche, nicht länger Erfahrungspunkte zu erhalten.');
