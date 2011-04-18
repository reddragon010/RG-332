-- boss immune mask
UPDATE creature_template SET mechanic_immune_mask=617299803 WHERE entry IN (16064,30603,16065,30601,30549,30600,16063,30602,15956,29249,15953,29268,15952,29278,15954,29615,15936,29701,16011,29718,16061,29940,16060,29955,16028,29324,15931,29373,15932,29417,15928,29448,15989,29991,15990,30061);

-- AnubRekhan
UPDATE creature_template SET dmg_multiplier=27 WHERE entry=15956;
UPDATE creature_template SET dmg_multiplier=54 WHERE entry=29249;
-- Crypt Guard
UPDATE creature_template SET dmg_multiplier=25 WHERE entry=16573;
UPDATE creature_template SET dmg_multiplier=25 WHERE entry=29256;
-- Corpse Scarabs hero
UPDATE creature_template SET mindmg=400, maxdmg=500, dmg_multiplier=5 WHERE entry=29267;
-- Faerlina
-- UPDATE creature_template SET dmg_multiplier=35 WHERE entry=15953;
UPDATE creature_template SET dmg_multiplier=47, equipment_id=1627 WHERE entry=29268;
-- Naxxramas Follower
UPDATE creature_template SET dmg_multiplier=40, equipment_id=1815 WHERE entry=29273;
-- Maexxna
UPDATE creature_template SET dmg_multiplier=20 WHERE entry=15952;
UPDATE creature_template SET dmg_multiplier=33 WHERE entry=29278;
-- Maexxna Spiderling
UPDATE creature_template SET dmg_multiplier=7 WHERE entry=17055;
UPDATE creature_template SET dmg_multiplier=7 WHERE entry=29279;
-- Noth the Plaguebringer
UPDATE creature_template SET dmg_multiplier=29 WHERE entry=15954;
UPDATE creature_template SET dmg_multiplier=43 WHERE entry=29615;
-- Plagued Warrior (1)
UPDATE creature_template SET dmg_multiplier=20, equipment_id=467 WHERE entry=29632;
-- Plagued Champion
UPDATE creature_template SET dmg_multiplier=20 WHERE entry=16983;
UPDATE creature_template SET dmg_multiplier=30, equipment_id=160 WHERE entry=29633;
--  Heigan the Unclean
UPDATE creature_template SET dmg_multiplier=20 WHERE entry=15936;
UPDATE creature_template SET dmg_multiplier=30, equipment_id=271 WHERE entry=29701;
-- Loatheb, Loatheb hero
UPDATE creature_template SET dmg_multiplier=15 WHERE entry=16011;
UPDATE creature_template SET dmg_multiplier=30 WHERE entry=29718;
-- Instructor Razuvious
-- UPDATE creature_template SET dmg_multiplier=290 WHERE entry=16061;
-- UPDATE creature_template SET dmg_multiplier=290 WHERE entry=29940;
-- Gothik adds (Gothik dont melee damage)
-- Unrelenting Trainee 
UPDATE creature_template SET dmg_multiplier=2 WHERE entry=16124;
UPDATE creature_template SET dmg_multiplier=4, equipment_id=1812 WHERE entry=29987;
-- Unrelenting Death Knight
UPDATE creature_template SET dmg_multiplier=6 WHERE entry=16125;
UPDATE creature_template SET dmg_multiplier=12, equipment_id=1813 WHERE entry=29985;
-- Unrelenting Rider
UPDATE creature_template SET dmg_multiplier=10 WHERE entry=16126;
UPDATE creature_template SET dmg_multiplier=20, equipment_id=1763 WHERE entry=29986;
-- Spectral Trainee
UPDATE creature_template SET dmg_multiplier=5 WHERE entry=16127;
UPDATE creature_template SET dmg_multiplier=3 WHERE entry=30264;
-- Spectral Death Knight
UPDATE creature_template SET dmg_multiplier=6 WHERE entry=16148;
UPDATE creature_template SET dmg_multiplier=12, equipment_id=1813 WHERE entry=29990;
-- Spectral Rider
UPDATE creature_template SET dmg_multiplier=11 WHERE entry=16150;
UPDATE creature_template SET dmg_multiplier=22, equipment_id=1763 WHERE entry=29988;
-- Spectral Horse
UPDATE creature_template SET dmg_multiplier=11 WHERE entry=16149;
UPDATE creature_template SET dmg_multiplier=22 WHERE entry=29989;
-- Four Horsemen
-- Thane Korthazz
UPDATE creature_template SET dmg_multiplier=35 WHERE entry=16064;
UPDATE creature_template SET dmg_multiplier=47, equipment_id=1720 WHERE entry=30603;
-- Baron Rivendare
UPDATE creature_template SET dmg_multiplier=40 WHERE entry=30549;
UPDATE creature_template SET dmg_multiplier=47, equipment_id=1763 WHERE entry=30600;
-- Grobbulus
UPDATE creature_template SET dmg_multiplier=40 WHERE entry=15931;
UPDATE creature_template SET dmg_multiplier=67 WHERE entry=29373;
-- Gluth
UPDATE creature_template SET dmg_multiplier=25 WHERE entry=15932;
UPDATE creature_template SET dmg_multiplier=40 WHERE entry=29417;
-- Thaddius
UPDATE creature_template SET dmg_multiplier=35 WHERE entry=15928;
UPDATE creature_template SET dmg_multiplier=60 WHERE entry=30603;
-- Stalagg
UPDATE creature_template SET dmg_multiplier=20 WHERE entry=15929;
UPDATE creature_template SET dmg_multiplier=40 WHERE entry=29446;
-- Feugen
UPDATE creature_template SET dmg_multiplier=20 WHERE entry=15930;
UPDATE creature_template SET dmg_multiplier=30 WHERE entry=30603;
-- Sapphiron
UPDATE creature_template SET dmg_multiplier=35 WHERE entry=15989;
UPDATE creature_template SET dmg_multiplier=55 WHERE entry=29991;
-- KelThuzad
-- UPDATE creature_template SET dmg_multiplier=25 WHERE entry=15990;
-- UPDATE creature_template SET dmg_multiplier=40 WHERE entry=30061;
-- Unstoppable Abomination
UPDATE creature_template SET dmg_multiplier=6 WHERE entry=16428;
UPDATE creature_template SET dmg_multiplier=6 WHERE entry=30603;