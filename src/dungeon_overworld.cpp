#include "dungeon_overworld.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_knight.h"
#include "bn_sprite_items_menuarrow.h"
#include "bn_regular_bg_items_map.h"

#include "bn_log.h"
#include "movement.h"
#include "duymmy_data.h"

namespace dungeon
{

    Overworld::Overworld() : Scene(),
                             map_bg_(bn::regular_bg_items::map.create_bg(0, 0)),
                             dog_sprite_(bn::sprite_items::knight.create_sprite(0, 0))
    {
        valid_tile_index_ =
            bn::regular_bg_map_cell_info(valid_map_cell_).tile_index();
    }
    int Overworld::increment_direction(int counter, int step)
    {
        int new_counter = counter + step;

        if (new_counter >= 4)
        {
            new_counter = 0;
        }
        else if (new_counter < 0)
        {
            new_counter = 3;
        }

        return new_counter;
    }

    coordinates Overworld::genereate_new_playerdir(direction d, int movement)
    {
        coordinates new_movement;
        new_movement.x = 0;
        new_movement.y = 0;

        switch (d)
        {
        case direction::east:
            new_movement.x = movement;
            break;

        case direction::west:
            new_movement.x = -movement;
            break;

        case direction::north:
            new_movement.y = -movement;
            break;

        case direction::south:
            new_movement.y = movement;
            break;

        default:
            BN_LOG("FUCK YOUUUUU");
            break;
        }

        return new_movement;
    }

    void Overworld::debug_logger(int x)
    {
        BN_LOG("Current Value of X:");
        BN_LOG(x);
    }

    bn::optional<scene_type> Overworld::update()
    {
        bn::point new_dog_map_position = dog_map_position_;

        if (bn::keypad::left_pressed())
        {
            player_dir_counter_ =
                increment_direction(player_dir_counter_, 1);

            debug_logger(player_dir_counter_);

            dog_sprite_.set_tiles(
                bn::sprite_items::knight.tiles_item(),
                player_dir_counter_);
        }
        else if (bn::keypad::right_pressed())
        {
            player_dir_counter_ =
                increment_direction(player_dir_counter_, -1);

            debug_logger(player_dir_counter_);

            dog_sprite_.set_tiles(
                bn::sprite_items::knight.tiles_item(),
                player_dir_counter_);
        }

        if (bn::keypad::up_pressed())
        {
            direction dir =
                static_cast<direction>(player_dir_counter_);

            coordinates new_movement =
                genereate_new_playerdir(dir, 1);

            int new_y =
                new_dog_map_position.y() + new_movement.y;

            int new_x =
                new_dog_map_position.x() + new_movement.x;

            new_dog_map_position.set_y(new_y);
            new_dog_map_position.set_x(new_x);
        }
        else if (bn::keypad::down_pressed())
        {
            direction dir =
                static_cast<direction>(player_dir_counter_);

            coordinates new_movement =
                genereate_new_playerdir(dir, -1);

            int new_y =
                new_dog_map_position.y() + new_movement.y;

            int new_x =
                new_dog_map_position.x() + new_movement.x;

            new_dog_map_position.set_y(new_y);
            new_dog_map_position.set_x(new_x);
        }
        if (bn::keypad::b_pressed()) {
            return dungeon::scene_type::MENU
        }

        bn::regular_bg_map_cell dog_map_cell =
            map_item_.cell(new_dog_map_position);

        int dog_tile_index =
            bn::regular_bg_map_cell_info(dog_map_cell).tile_index();

        if (dog_tile_index == valid_tile_index_)
        {
            dog_map_position_ = new_dog_map_position;
        }

        bn::fixed dog_sprite_x =
            bn::fixed(dog_map_position_.x() * 8) -
            bn::fixed(map_item_.dimensions().width() * 4) +
            bn::fixed(4);

        bn::fixed dog_sprite_y =
            bn::fixed(dog_map_position_.y() * 8) -
            bn::fixed(map_item_.dimensions().height() * 4) +
            bn::fixed(4);

        dog_sprite_.set_position(dog_sprite_x, dog_sprite_y);

        return bn::nullopt;
    }

}
