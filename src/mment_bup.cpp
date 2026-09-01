//
//
// #include "bn_core.h"
// #include "bn_keypad.h"
// #include "bn_regular_bg_ptr.h"
// #include "bn_sprite_text_generator.h"
// #include "bn_regular_bg_map_cell_info.h"
//
// #include "bn_sprite_items_dog.h"
// #include "bn_sprite_items_tinyarrow2.h"
// #include "bn_regular_bg_items_map.h"
//
// #include "common_info.h"
// #include "common_variable_8x16_sprite_font.h"
// #include "bn_log.h"
// #include "bn_format.h"
// #include <array>
//
// enum class direction
// {
//     east = 0,
//     north = 1,
//     west = 2,
//     south = 3
// };
//
// constexpr std::array<int, 4> playerAngles = {0, 90, 180, 270};
//
// struct coordinates
// {
//     int x;
//     int y;
// };
//
// class Movement
// {
// public:
//     direction player_direction;
//     std::array<int, 4> playerAngles;
//     coordinates current_coordinates;
//     int valid_tile_index;
//     int player_dir_counter;
//     bn::regular_bg_ptr map_bg;
//     bn::sprite_ptr dog_sprite;
//     bn::point dog_map_position;
//     bn::regular_bg_map_item map_item; 
//     bn::regular_bg_map_cell valid_map_cell;
//
//
//     Movement(bn::regular_bg_ptr &map_bg_param, bn::sprite_ptr &dog_sprite_param) :
//         map_bg(map_bg_param),
//         dog_sprite(dog_sprite_param),
//         dog_map_position(16, 16),
//         map_item(bn::regular_bg_items::map.map_item()),
//         valid_map_cell(map_item.cell(0, 0))
//     {
//         bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
//
//         // this->map_bg = bn::regular_bg_items::map.create_bg(0, 0);
//         // this->dog_sprite = bn::sprite_items::tinyarrow2.create_sprite(0, 0);
//
//         this->valid_tile_index = bn::regular_bg_map_cell_info(valid_map_cell).tile_index();
//
//         // bn::point dog_map_position(16, 16);
//         player_dir_counter = 0;
//     }
//
//     int increment_direction(int counter, int step)
//     {
//         int new_counter = counter + step;
//         if (new_counter >= 4)
//         {
//             new_counter = 0;
//         }
//         else if (new_counter < 0)
//         {
//             new_counter = 3;
//         }
//         return new_counter;
//     }
//
//     coordinates genereate_new_playerdir(direction d, int movement)
//     {
//         coordinates new_movement;
//         new_movement.x = 0;
//         new_movement.y = 0;
//         switch (d)
//         {
//         case direction::east:
//             new_movement.x = movement;
//             break;
//         case direction::west:
//             new_movement.x = -movement;
//             break;
//         case direction::north:
//             new_movement.y = -movement;
//             break;
//         case direction::south:
//             new_movement.y = movement;
//             break;
//         default:
//             BN_LOG("FUCK YOUUUUU");
//             break;
//         }
//         return new_movement;
//     }
//
//     void debug_logger(int x)
//     {
//         // {} acts as the placeholder for variables
//         BN_LOG("Current Value of X:");
//         BN_LOG(x);
//     }
//     void update()
//     {
//         bn::point new_dog_map_position = dog_map_position;
//
//         if (bn::keypad::left_pressed())
//         {
//             // new_dog_map_position.set_x(new_dog_map_position.x() - 1);
//             // dog_sprite.set_horizontal_flip(true);
//             player_dir_counter = increment_direction(player_dir_counter, 1);
//
//             debug_logger(player_dir_counter);
//             dog_sprite.set_rotation_angle(playerAngles[player_dir_counter]);
//             // dog_sprite.set_rotation_angle(90);
//         }
//         else if (bn::keypad::right_pressed())
//         {
//             // new_dog_map_position.set_x(new_dog_map_position.x() + 1);
//             player_dir_counter = increment_direction(player_dir_counter, -1);
//             // dog_sprite.set_horizontal_flip(false);
//             debug_logger(player_dir_counter);
//             dog_sprite.set_rotation_angle(playerAngles[player_dir_counter]);
//         }
//
//         if (bn::keypad::up_pressed())
//         {
//
//             direction dir = static_cast<direction>(player_dir_counter);
//             coordinates new_movement = genereate_new_playerdir(dir, 1);
//             int new_y = new_dog_map_position.y() + new_movement.y;
//             int new_x = new_dog_map_position.x() + new_movement.x;
//             new_dog_map_position.set_y(new_y);
//             new_dog_map_position.set_x(new_x);
//
//             // dog_sprite.set_rotation_angle(90);
//         }
//         else if (bn::keypad::down_pressed())
//         {
//
//             direction dir = static_cast<direction>(player_dir_counter);
//             coordinates new_movement = genereate_new_playerdir(dir, -1);
//             int new_y = new_dog_map_position.y() + new_movement.y;
//             int new_x = new_dog_map_position.x() + new_movement.x;
//             new_dog_map_position.set_y(new_y);
//             new_dog_map_position.set_x(new_x);
//             // dog_sprite.set_rotation_angle(270);
//         }
//
//         bn::regular_bg_map_cell dog_map_cell = map_item.cell(new_dog_map_position);
//         int dog_tile_index = bn::regular_bg_map_cell_info(dog_map_cell).tile_index();
//
//         if (dog_tile_index == valid_tile_index)
//         {
//             dog_map_position = new_dog_map_position;
//         }
//
//         bn::fixed dog_sprite_x = (dog_map_position.x() * 8) - (map_item.dimensions().width() * 4) + 4;
//         bn::fixed dog_sprite_y = (dog_map_position.y() * 8) - (map_item.dimensions().height() * 4) + 4;
//         dog_sprite.set_position(dog_sprite_x, dog_sprite_y);
//     }
// };
