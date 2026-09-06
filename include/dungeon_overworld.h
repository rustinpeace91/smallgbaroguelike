#ifndef DUNGEON_OVERWORLD_H
#define DUNGEON_OVERWORLD_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"

#include "dungeon_scene.h"
#include <array>

namespace dungeon
{

    enum class direction
    {
        east = 0,
        north = 1,
        west = 2,
        south = 3
    };

    constexpr std::array<int, 4> playerAngles = {0, 90, 180, 270};

    struct coordinates
    {
        int x;
        int y;
    };

    class Overworld : public Scene
    {
    public:
        Overworld();
        bn::optional<scene_type> update() override;

    private:
        direction player_direction = direction::east;
        coordinates current_coordinates{0, 0};
        int player_dir_counter_ = 0;
        int valid_tile_index_ = 0;

        bn::regular_bg_ptr map_bg_ = bn::regular_bg_items::map.create_bg(0, 0);
        bn::sprite_ptr dog_sprite_ = bn::sprite_items::knight.create_sprite(0, 0);

        bn::point dog_map_position_ = bn::point(16, 16);
        bn::regular_bg_map_item map_item_ = bn::regular_bg_items::map.map_item();
        bn::regular_bg_map_cell valid_map_cell_ = map_item_.cell(0, 0);
    };

}

#endif
