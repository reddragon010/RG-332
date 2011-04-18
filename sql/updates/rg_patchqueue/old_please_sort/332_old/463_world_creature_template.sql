-- 0000880: SCHERBENWELT - Gladiator des Astraleums
update `creature_template` set `faction_A`=16, `faction_H`=16, `unit_flags`=0 WHERE `entry`=20854;

-- 0000900: NORDEND - Besorgt den Schlüssel
UPDATE `creature_template` SET `faction_A`=1771, `lootid`=29915, `pickpocketloot`=29915, `Killcredit1`=0, `minlevel`=80, `maxlevel`=80, `attackpower`=708, `mindmg`=594, `maxdmg`=793, `questItem2`=0, `questItem3`=0, `questItem1`=0, `mingold`=1000, `maxgold`=3000, `faction_H`=1771 WHERE `entry`=29915;
