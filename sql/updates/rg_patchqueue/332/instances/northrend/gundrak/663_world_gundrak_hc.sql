-- Der wilde Eck
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=29932;

-- Schlangen 2ter boss
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16 WHERE `entry`=29713;

-- Endboss Gundrak Adds
UPDATE `creature_template` SET `faction_A`=16, `faction_H`=16, `mindmg`=450, `maxdmg`=610, `minlevel`=77, `maxlevel`=80, `attackpower`=2000 WHERE `entry`=29791;

UPDATE `creature_template` SET `mindmg`=387, `maxdmg`=543, `attackpower`=528, `dmg_multiplier`=9, `minrangedmg`=324, `maxrangedmg`=480, `rangedattackpower`=88 WHERE `entry`=29932;

-- Gundrak 2 bosse loot
UPDATE `reference_loot_template` SET `item`=40752 WHERE `entry`=35040 AND `item`=47241;

UPDATE `creature_template` SET `unit_flags`=32768 WHERE `entry`=29791;
