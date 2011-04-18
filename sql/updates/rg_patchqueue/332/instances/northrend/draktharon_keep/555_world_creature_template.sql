
UPDATE creature_template SET unit_flags=unit_flags|2|33554432, flags_extra=flags_extra|2 WHERE entry IN (26620,31339);
-- novos fight 
UPDATE creature_template SET mindmg=204, maxdmg=364, dmg_multiplier=7.5 WHERE entry=27597;
UPDATE creature_template SET mindmg=264, maxdmg=304, dmg_multiplier=13 WHERE entry=31348;
UPDATE creature_template SET mindmg=100, maxdmg=204, dmg_multiplier=7.5 WHERE entry=27598;
UPDATE creature_template SET mindmg=104, maxdmg=204, dmg_multiplier=13 WHERE entry=31873;
UPDATE creature_template SET mindmg=150, maxdmg=204, dmg_multiplier=7.5  WHERE entry=27600;
UPDATE creature_template SET mindmg=204, maxdmg=354, dmg_multiplier=13 WHERE entry=31356;
UPDATE creature_template SET mindmg=100, maxdmg=204, dmg_multiplier=7.5 WHERE entry=32786;
UPDATE creature_template SET mindmg=104, maxdmg=204, dmg_multiplier=13 WHERE entry=32787;
UPDATE creature_template SET mindmg=200, maxdmg=304, dmg_multiplier=7.5 WHERE entry=26627;
UPDATE creature_template SET mindmg=204, maxdmg=304, dmg_multiplier=13 WHERE entry=31344;

UPDATE creature_template SET unit_flags=unit_flags&~2&~33554432 WHERE entry IN (26638,31351);

UPDATE creature_template SET faction_A=14, faction_H=14,mindmg=200, maxdmg=304, dmg_multiplier=7.5 WHERE entry=26824;
UPDATE creature_template SET faction_A=14, faction_H=14,mindmg=200, maxdmg=304, dmg_multiplier=13 WHERE entry=31341;

DELETE FROM creature WHERE guid in(127478,127479,127480,127481,127482,127483,127484,127485,127486,127487,127488);
-- The Prophet Tharon'ja (Normal and Heroic)
UPDATE creature_template SET mindmg=400, maxdmg=464, dmg_multiplier=7.5 WHERE entry=26632;
UPDATE creature_template SET mindmg=500, maxdmg=654, dmg_multiplier=13 WHERE entry=31360;
-- Ingvar the plunderer
UPDATE creature_template SET mindmg=400, maxdmg=464, dmg_multiplier=7.5 WHERE entry=23980;
UPDATE creature_template SET mindmg=500, maxdmg=654, dmg_multiplier=13 WHERE entry=31674;
-- Trollgore,Novos,King Dred,The Prophet Tharon'ja,Ingvar the plunderer
UPDATE creature_template SET mechanic_immune_mask=638270294 WHERE entry IN(26630,31362,26631,31350,27483,31349,26632,31360,3980,31674);