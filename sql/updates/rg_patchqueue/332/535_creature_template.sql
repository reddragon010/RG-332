-- AV Horden Boss DMG anpassen
UPDATE `creature_template` SET `mindmg`=6000, `maxdmg`=6500, `dmg_multiplier`=1 WHERE `entry`=31819;

-- AV Allianz Boxx DM anpassen
UPDATE `creature_template` SET `mindmg`=6000, `maxdmg`=6500, `dmg_multiplier`=1 WHERE `entry`=31818;

-- AV Horde zwischen Boss
UPDATE `creature_template` SET `mindmg`=4500, `maxdmg`=5000, `dmg_multiplier`=1, `Health_mod`=3 WHERE `entry`=31055;

-- AV Allianz zwischen Boss
UPDATE `creature_template` SET `mindmg`=4500, `maxdmg`=5000, `dmg_multiplier`=1 WHERE `entry`=31820;

-- AV Horden Boss Wachen
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=32091;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=31981;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=31966;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=31968;

-- AV Allianz Boxx Wachen
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=32008;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=32086;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=31972;
UPDATE `creature_template` SET `mindmg`=3600, `maxdmg`=3800, `dmg_multiplier`=1 WHERE `entry`=32007;

-- AV World NPC Allianz
UPDATE `creature_template` SET `mindmg`=1800, `maxdmg`=2100, `dmg_multiplier`=1 WHERE `entry`=31909;

-- AV World NPC Horde
UPDATE `creature_template` SET `mindmg`=1800, `maxdmg`=2100, `dmg_multiplier`=1 WHERE `entry`=31829;

-- AV Allianz Faction
UPDATE creature_template set faction_A=1216,faction_H=1216 where entry in (32046,32008);

