#include "dungeon_menu.h"
#include "bn_utility.h" // Required for bn::move if you use it

namespace dungeon
{

    // Use the constructor initialization list to set your private variable
    PlayerMenu::PlayerMenu(bn::sprite_text_generator text_generator)
        : text_generator_(bn::move(text_generator))
    {
        // Additional setup
    }

    bn::optional<scene_type> PlayerMenu::update()
    {
        // Your update logic here
        return bn::nullopt;
    }

}