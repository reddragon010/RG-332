-- set loot of Ingvar the Plunderer (Undead) to the loot of Ingvar the Plunderer (Human)
-- normal loot
UPDATE creature_template SET lootid=0 WHERE entry=23954;
UPDATE creature_template SET lootid=23980 WHERE entry=23980;
UPDATE creature_loot_template SET entry=23980 WHERE entry=23954;

-- heroic loot
UPDATE creature_template SET lootid=0 WHERE entry=31673;
UPDATE creature_template SET minlevel=81, maxlevel=81, lootid=31674 WHERE entry=31674;
UPDATE creature_loot_template SET entry=31674 WHERE entry=31673;