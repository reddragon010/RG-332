-- SOTA sql fixes
update creature_template set speed_walk=0,speed_run=0 where entry in (27894,32795)