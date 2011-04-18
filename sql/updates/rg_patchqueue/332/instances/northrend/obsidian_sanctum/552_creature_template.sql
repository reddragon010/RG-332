-- Eieraufseher fix, sind weiterhin unsichtbar greifen aber nicht mehr an
update creature_template set faction_A=35,faction_H=35 where entry in (31138,31550);