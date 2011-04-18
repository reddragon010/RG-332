-- Adds Lok'Lira's bargain disguise spell to the spell_area table so when you leave the brunhildar village area the disguise is removed
DELETE FROM `spell_area` WHERE spell=72914;
INSERT INTO `spell_area` (`spell`,`area`,`aura_spell`,`autocast`) VALUES 
(72914,4422,55012,1),
(72914,4425,55012,1),
(72914,4437,55012,1),
(72914,4438,55012,1),
(72914,4535,55012,1);

