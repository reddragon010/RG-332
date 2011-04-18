--
-- MAJOR FIX: Delete questrelation from quest 'Breaking the Blocakade'
-- Info: bomb can be used against hi-lvl mobs
-- Quest: 11153
-- Questgiver: 23895
--
DELETE FROM creature_questrelation WHERE id=23895 AND quest=11153;
