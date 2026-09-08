#ifndef DUNGEON_PLAYER_MENU_H
#define DUNGEON_PLAYER_MENU_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
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
    };

}
