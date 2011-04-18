-- Fixes error when buying items with RequiredReputationRank != 0 but RequiredReputationFaction = 0
UPDATE `item_template` SET `RequiredReputationRank` =0 WHERE `RequiredReputationRank` !=0 AND `RequiredReputationFaction` =0;
