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
#include "bn_sprite_items_menuarrow.h"
#include "bn_regular_bg_items_map.h"

#include "common_info.h"
#include "common_variable_8x16_sprite_font.h"
#include "bn_log.h"
#include "bn_format.h"
#include <array>
#include "movement.h"
#include "duymmy_data.h"
#include "bn_sprite_palette_ptr.h"

enum modes {
    MOVE, MENU, INVENTORY
};


modes game_mode = MOVE;
enum class menu_options
{
    inventory = 0,
    options = 1,
    magic = 2
};

void generate_menu_text(
    bn::sprite_text_generator& text_generator,
    bn::vector<bn::sprite_ptr, 128>& menu_text_sprites)
{
    int text_start_x = 55;
    int text_start_y = 0;

    int text_x = text_start_x;
    int text_y = text_start_y;

    for(const char* option : DummyData::MAIN_MENU_OPTIONS)
    {
        text_generator.generate(
            text_x,
            text_y,
            bn::string_view(option),
            menu_text_sprites
        );

        text_y += 20;
    }
}

void generate_inventory_menu_text(
    bn::sprite_text_generator& text_generator,
    bn::vector<bn::sprite_ptr, 128>& menu_text_sprites,
    int page_start,
    int page_end
){
    // paginate
    // DummyData::INVENTORY
};

int main()
{


    bn::core::init();


    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    // common::info info("Map collision", info_text_lines, text_generator);

    bn::regular_bg_ptr map_bg = bn::regular_bg_items::map.create_bg(0, 0);
    bn::sprite_ptr dog_sprite = bn::sprite_items::tinyarrow2.create_sprite(0, 0);
    Movement movementInstance(map_bg, dog_sprite);
    
    //
    //
    //
    // MENU STUFF
    // ARROW
    bn::sprite_ptr menu_box = bn::sprite_items::bg.create_sprite(0, 0);
    bn::sprite_ptr menu_arrow = bn::sprite_items::menuarrow.create_sprite(0,0);

    bn::sprite_palette_ptr arrow_palette = menu_arrow.palette();

    // TURN ARROW YELLOW
    bn::color arrow_original_color = arrow_palette.colors()[1]; 
    bn::color yellow_color(31, 31, 0);

    int flash_counter = 0;
    bool is_yellow = false;

    // MENU BOX
    int menu_width = 75;
    int menu_height = 100;
    int arrow_position_x = 50;
    int arrow_reset = 0;
    int arrow_position_y = -20;
    int menu_position_index = 0;
    int menu_size = std::ssize(DummyData::MAIN_MENU_OPTIONS);
    bn::fixed horizontal_scale = bn::fixed(menu_width) / 64;
    bn::fixed vertical_scale = bn::fixed(menu_height) / 64;
    menu_box.set_scale(horizontal_scale, vertical_scale);
    menu_box.set_position(0  + (120 -(menu_width/2)), 0 + (80 - (menu_height/2)));
    menu_box.set_visible(false);

    // MENU TEXT
    bn::vector<bn::sprite_ptr, 128> menu_text_sprites;


    while(true)
    {
        if(bn::keypad::b_pressed()){
            if(game_mode == MOVE){
                game_mode = MENU;
                generate_menu_text(text_generator, menu_text_sprites);
                menu_box.set_visible(true);
                menu_arrow.set_visible(true);
            } else {
                // MAIN MENU
                menu_position_index = 0;
                game_mode = MOVE;
                menu_text_sprites.clear();
                menu_box.set_visible(false);
                menu_arrow.set_visible(false);
            }
        }


        // Example trigger: Press A button to make the arrow yellow for 1 second
        if(bn::keypad::a_pressed() && !is_yellow)
        {
            arrow_palette.set_color(1, yellow_color); // Change arrow to yellow
            flash_counter = 30;                        // 60 frames = 1 second
            is_yellow = true;
            if(menu_position_index == static_cast<int>(menu_options::inventory)){
                menu_position_index = 0;
                game_mode = INVENTORY;
                menu_text_sprites.clear();
                // menu_box.set_visible(false);
                // reset arrow
                // determine pagination values
                // show up and down arrows
            }
        }

        // Countdown timer logic
        if(is_yellow)
        {
            flash_counter--;
            if(flash_counter <= 0)
            {
                arrow_palette.set_color(1, arrow_original_color); // Restore original color
                is_yellow = false;
            }
        }

        if(bn::keypad::up_pressed()){
            if(menu_position_index > 0){
                menu_position_index--;
            }
        }
        if(bn::keypad::down_pressed()){
            if(menu_position_index < menu_size - 1){
                menu_position_index++;
            }
        }
        // info.update();
        if(game_mode == MOVE){
            movementInstance.update();
        } else {
            menu_arrow.set_x(bn::fixed(arrow_position_x));
            menu_arrow.set_y(bn::fixed(arrow_position_y  + 20 * (menu_position_index + 1)));
        }
        bn::core::update();
    }
}
