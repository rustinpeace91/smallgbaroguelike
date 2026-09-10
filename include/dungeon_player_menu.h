#ifndef DUNGEON_PLAYER_MENU_H
#define DUNGEON_PLAYER_MENU_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include "dungeon_scene.h"
#include <array>

namespace dungeon
{
    class PlayerMenu : public Scene
    {
    public:
        PlayerMenu(bn::sprite_text_generator&);
        bn::optional<scene_type> update() override;

    private:
        bn::sprite_text_generator text_generator_;
        bn::sprite_ptr menu_box_;
        int menu_width = 75;
        int menu_height = 100;
        int arrow_position_x = 50;
        int arrow_reset = 0;
        int arrow_position_y = -20;
        int menu_position_index = 0;
        bn::fixed horizontal_scale = bn::fixed(menu_width) / 64;
        bn::fixed vertical_scale = bn::fixed(menu_height) / 64;

    };

}
#endif
