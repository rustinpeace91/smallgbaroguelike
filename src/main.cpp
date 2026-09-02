/*
 * Copyright (c) 2020-2026 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_map_cell_info.h"

#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_dog.h"
#include "bn_sprite_items_tinyarrow2.h"
#include "bn_regular_bg_items_map.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_log.h"
#include "bn_format.h"
#include <array>
#include "movement.h"

enum modes {
    MOVE, MENU
};

modes game_mode = MOVE;

int main()
{


    bn::core::init();


    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    // common::info info("Map collision", info_text_lines, text_generator);

    bn::regular_bg_ptr map_bg = bn::regular_bg_items::map.create_bg(0, 0);
    bn::sprite_ptr dog_sprite = bn::sprite_items::tinyarrow2.create_sprite(0, 0);
    Movement movementInstance(map_bg, dog_sprite); // Create instance of the class
    // constexpr bn::string_view info_text_lines[] = {
    //     "PAD: Move player"
    // };
    //
    //
    //
    // MENU STUFF
    bn::sprite_ptr menu_box = bn::sprite_items::bg.create_sprite(0, 0);
    int menu_width = 60;
    int menu_height = 100;
    bn::fixed horizontal_scale = bn::fixed(menu_width) / 64;
    bn::fixed vertical_scale = bn::fixed(menu_height) / 64;
    menu_box.set_scale(horizontal_scale, vertical_scale);
    menu_box.set_position(0  + (120 -(menu_width/2)), 0 + (80 - (menu_height/2)));
    // menu_box.set_vertical_scale(-1);

    while(true)
    {
        if(bn::keypad::b_pressed()){
            if(game_mode == MOVE){
                game_mode = MENU;
            } else {
                game_mode = MOVE;
            }
        }
        // info.update();
        if(game_mode == MOVE){
            movementInstance.update();

            menu_box.set_visible(false);
        } else {
            menu_box.set_visible(true);
        }
        bn::core::update();
    }
}
