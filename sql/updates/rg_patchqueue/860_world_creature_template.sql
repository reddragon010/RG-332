UPDATE `creature_template` SET `ScriptName` = 'npc_archmage_vargoth' WHERE `entry` = 19481;

-- Text data from Sniff
DELETE FROM `npc_text` WHERE `id` IN (31000, 31001);
INSERT INTO `npc_text` (`ID`, `text0_0`) VALUES 
('31000', 'Welcome $c, to my humble retreat. I find this place very relaxing and I have always loved being at home in Dalaran. Sometimes though, it can be such a lonely place... such a lonely place.'),
('31001', 'Amazing! There are passages in here that I have never seen before. This must have taken quite a while for you to track down. If you ever find anymore books like this, I would like to be notified immediately. Please take one of my Kirin Tor Familiars with you just in case you stumble across anything.');