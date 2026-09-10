
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_unique_ptr.h"
#include "bn_sprite_text_generator.h"

// #include "bn_sprite_text_generator.h"
// #include "bn_regular_bg_map_cell_info.h"
//
#include "dungeon_scene.h"
#include "dungeon_scene_type.h"
#include "dungeon_overworld.h"
#include "dungeon_player_menu.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    bn::core::init();

    // text,assets etc. will go here

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    // assets end
    bn::unique_ptr<dungeon::Scene> scene(
        new dungeon::Overworld()
    );

    bn::optional<dungeon::scene_type> next_scene = dungeon::scene_type::OVERWORLD;
    int wait_frames = 0;

    while(true){
        if(scene){
            next_scene = scene->update();
        }
        // if no next_scene, just keep going
        //
        if(next_scene){
            // scene change logic will go here, 
            // switch statement on next_scene
            switch(*next_scene){
                case dungeon::scene_type::OVERWORLD:
                    scene.reset(new dungeon::Overworld());
                    break;
                case dungeon::scene_type::MENU:
                    scene.reset(new dungeon::PlayerMenu(text_generator));
                    break;
                default:
                    break;
            }
            // smart pointer (?) owernship will change here
        }

        bn::core::update();
    };

}
