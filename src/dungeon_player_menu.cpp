#include "dungeon_player_menu.h"
#include "dungeon_scene_type.h"
#include "bn_sprite_items_bg.h"

namespace dungeon {

// Use the constructor initialization list to set your private variable
PlayerMenu::PlayerMenu(bn::sprite_text_generator& text_generator)
    : Scene(),
      text_generator_(text_generator),
      menu_box_(bn::sprite_items::bg.create_sprite(0, 0)) 
{
  menu_box_.set_position(0 + (120 - (menu_width / 2)),
                        0 + (80 - (menu_height / 2)));
  bn::fixed horizontal_scale = bn::fixed(menu_width) / 64;
  bn::fixed vertical_scale = bn::fixed(menu_height) / 64;
  menu_box_.set_scale(horizontal_scale, vertical_scale);
  menu_box_.set_visible(true);
}

bn::optional<dungeon::scene_type> PlayerMenu::update() {
  // Your update logic here
  if (bn::keypad::b_pressed()) {
    return dungeon::scene_type::OVERWORLD;
  }
  return bn::nullopt;
}

} // namespace dungeon
