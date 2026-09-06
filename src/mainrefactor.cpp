
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_unique_ptr.h"
#include "bn_sprite_text_generator.h"

#include "scene_type.h"
// #include "bn_sprite_text_generator.h"
// #include "bn_regular_bg_map_cell_info.h"
//
#include "dungeon_scene.h"
#include "common_variable_8x16_sprite_font.h"

int main()
{
    bn::core::init();

    // text,assets etc. will go here

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    // assets end
    bn::unique_ptr<dungeon::scene> scene(
        // namespace aint working. sort it out
        new dungeon::overworld(text_generator);
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
            // smart pointer (?) owernship will change here
        }

        bn::core::update();
    };

}
