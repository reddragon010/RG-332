-- Concerted Efforts (Alliance)

REPLACE INTO `quest_template` VALUES(13477, 0, -25, 0, 71, 0, -1, 41, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 13478, 0, 0, 0, 0, 0, 0, 0, 'Concerted Efforts', '', '', 'You live up to yer reputation, $N. Without people like you, the Alliance wouldn''t stand a chance against the savage forces of the Horde.', 'Ah, $N. I hope you continue to lend your experience to the different battlefronts. A lot of our lads and lasses in the field look up to seasoned veterans like you.', '', 'NULL', '', '', '', '', 42425, 20559, 20558, 29024, 20560, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 730, 509, 890, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11403);

REPLACE INTO `quest_template` VALUES(13478, 1, -25, 0, 71, 0, -1, 41, 1101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 'Concerted Efforts', 'We''re not fighting isolated battles against the Horde anymore, $g lad:lass;.$B$BVictory in one front means denying the Horde resources they''d use against us in a different battle.  By the same token, abandoning any given battle could give the advantage to our opponent somewhere else around the world.$B$BThe Alliance is in need of more combatants with this sort of worldly understanding... truly seasoned veterans!  $N, come back to me after you''ve served against the Horde at all of our active battlegrounds.', 'Bring a Mark of Honor from each battleground to an Alliance Brigadier General in any Alliance Capital City, Shattrath, Dalaran, or Wintergrasp.', 'You''re not one to disappoint, $n! What you''ve learned goes beyond petty medals and commendations. What you''ve learned is what can only come with experience and the hardening of one''s temper in the field of battle.$b$bYou''ve done well, $c. You''re a true hero of the Alliance!', 'How are yer travels faring $gladdie:lassy;?', '', 'Return to Alliance Brigadier General.', '', '', '', '', 42425, 20559, 20558, 29024, 20560, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 509, 730, 890, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 7, 74000, 132300, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11159);

DELETE FROM `creature_involvedrelation` WHERE `id` = 15351 AND `quest` IN (13477, 13478);

INSERT INTO `creature_involvedrelation` VALUES(15351, 13477), (15351, 13478);

DELETE FROM `creature_questrelation` WHERE `id` = 15351 AND `quest` IN (13477, 13478);

INSERT INTO `creature_questrelation` VALUES(15351, 13477), (15351, 13478);

-- For Great Honor (Horde)

REPLACE INTO `quest_template` VALUES(13475, 0, -25, 0, 71, 0, -1, 41, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 1, 0, 0, 0, 0, 13476, 0, 0, 0, 0, 0, 0, 0, 'For Great Honor', '', '', 'You continue to honor the Horde, $N. I''m glad to see you haven''t turned soft.', 'Arathi is still wet with the blood of great warriors and the clash of steel still rings throughout Alterac. Do not waste my time unless you bring news from the front!', '', NULL, '', '', '', '', 42425, 20559, 20558, 29024, 20560, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 729, 889, 510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);

REPLACE INTO `quest_template` VALUES(13476, 1, -25, 0, 71, 0, -1, 41, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 'For Great Honor', 'Serving the Horde in one of the great battles against the Alliance is a source of great honor!  The few however, that have served the Horde in ALL of our active battlefronts are our truly great fighters.  We shall vanquish our opponents, not by fighting isolated skirmishes, but by waging a well-coordinated war.$B$BGo forth and crush the Alliance on every front!  For Honor!  For the Horde!', 'Bring a Mark of Honor from each battleground to a Horde Warbringer in any Horde capital city, Shattrath, Dalaran, or Wintergrasp.', 'Your trials have not been easy, but your courage did not escape you and your strength did not fail. Part with past tokens of victory, $c. None shall need them as a reminder of your worth. Stand up straight, $n. Today you will walk with great pride for you are a hero!', 'Arathi is still wet with the blood of great warriors and the clash of steel still rings throughout Alterac. Do not waste my time unless you bring news from the front!', '', NULL, '', '', '', '', 20558, 20559, 42425, 29024, 20560, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 729, 889, 510, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 74000, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);

DELETE FROM `creature_involvedrelation` WHERE `id` = 15350 AND `quest` IN (13475, 13476);

INSERT INTO `creature_involvedrelation` 
VALUES(15350, 13475), (15350, 13476);

DELETE FROM `creature_questrelation` WHERE `id` = 15350 AND `quest` IN (13475, 13476);

INSERT INTO `creature_questrelation` 
VALUES (15350, 13475), (15350, 13476);
