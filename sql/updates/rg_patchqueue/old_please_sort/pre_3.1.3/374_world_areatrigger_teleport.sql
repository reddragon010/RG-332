-- Last Rites Portals

DELETE FROM `areatrigger_teleport` WHERE `id` IN (5332, 5334, 5338, 5340);

INSERT INTO `areatrigger_teleport` (`id`, `name`, `access_id`, `target_map`, `target_position_x`, `target_position_y`, `target_position_z`, `target_orientation`) VALUES
(5332, 'Last Rites bottom to middle', 45, 571, 3734, 3563, 290.81, 3.72),
(5334, 'Last Rites middle to bottom', 45, 571, 3801, 3586, 49.5, 1.21),
(5338, 'Last Rites top to middle', 45, 571, 3738, 3562, 298.522, 4.56),
(5340, 'Last Rites middle to top', 45, 571, 3688.87, 3577.15, 473.322, 6);
