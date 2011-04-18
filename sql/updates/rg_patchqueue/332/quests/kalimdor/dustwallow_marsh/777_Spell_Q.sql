-- Spell fix
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (42287);

INSERT INTO `spell_linked_spell`
	(`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES
	(42287, 42288, 0, 0);