-- Fix crash alerts at startup

UPDATE `creature_template` SET `ScriptName`='npc_forest_frog' WHERE (`entry`='24396') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_tyrion' WHERE (`entry`='7766') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_tyrion_spybot' WHERE (`entry`='8856') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_lord_gregor_lescovar' WHERE (`entry`='1754') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='mob_ichor_globule' WHERE (`entry`='29321') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_marzon_silent_blade' WHERE (`entry`='1755') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='mob_ethereal_sphere' WHERE (`entry`='29271') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_gurgthock' WHERE (`entry`='30007') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_orinoko_tuskbreaker' WHERE (`entry`='30020') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_korrak_bloodrager' WHERE (`entry`='30023') LIMIT 1;
UPDATE `creature_template` SET `ScriptName`='npc_yggdras' WHERE (`entry`='30014') LIMIT 1;