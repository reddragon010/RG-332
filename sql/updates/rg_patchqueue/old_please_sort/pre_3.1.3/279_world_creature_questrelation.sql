-- DEPRECIATED WARSONG GULCH QUESTS
-- INFO: Mark of Honor, Quell the Silverwing Usurpers
--       Talismans of Merit, Vanquish the Invaders!
DELETE FROM creature_questrelation WHERE quest IN( 7922, 7923, 7924, 7925, 8293, 7789, 7874, 7875, 7876, 8294, 7886, 7887, 7888, 7921, 8292, 7788, 7871, 7872, 7873, 8291 );
DELETE FROM creature_involvedrelation WHERE quest IN( 7922, 7923, 7924, 7925, 8293, 7789, 7874, 7875, 7876, 8294, 7886, 7887, 7888, 7921, 8292, 7788, 7871, 7872, 7873, 8291 );

-- DEPRECIATED ARATHIBASIN QUESTS
-- INFO: Arathi Basin Resources!, Cut Arathor Supply Lines
--       More Resource Crates
DELETE FROM creature_questrelation WHERE quest IN( 8080, 8154, 8155, 8156, 8297, 8123, 8160, 8161, 8162, 8299, 8081, 8157, 8158, 8159, 8298, 8124, 8163, 8164, 8165, 8300 );
DELETE FROM creature_involvedrelation WHERE quest IN( 8080, 8154, 8155, 8156, 8297, 8123, 8160, 8161, 8162, 8299, 8081, 8157, 8158, 8159, 8298, 8124, 8163, 8164, 8165, 8300 );

-- DEPRICIATED ALTERAC VALLEY QUESTS
-- INFO: 8369, 8375, 8383, 8387 already removed!
