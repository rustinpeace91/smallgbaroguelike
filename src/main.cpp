
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "scene_type.h"
// #include "bn_sprite_text_generator.h"
// #include "bn_regular_bg_map_cell_info.h"

int main()
{
    bn::core::init();

    // text,assets etc. will go here
    //
    // assets end
    int wait_frames = 0;
    bn::unique_ptr<db::scene> scene(
        // namespace aint working. sort it out
        new db::overworld() //params
    )

    bn::optional<db::scene_type> next_scene = db::scene_type::OVERWORLD

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
    }

}
