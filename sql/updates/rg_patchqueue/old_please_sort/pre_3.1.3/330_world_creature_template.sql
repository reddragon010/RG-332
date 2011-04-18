-- no XP for totems
UPDATE `creature_template` set `flags_extra` = `flags_extra`|64 WHERE !( `flags_extra` &64 ) AND `name` LIKE "%totem%";