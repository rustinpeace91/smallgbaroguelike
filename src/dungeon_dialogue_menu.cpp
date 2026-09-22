#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "dungeon_dialogue_menu.h"

//------TEXBOX IMPORTS --------
#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_menuarrow.h"
#include "dummy_data.h"
#include "bn_log.h"

namespace dungeon{
  DungeonDialogueMenu::DungeonDialogueMenu(
    bn::sprite_ptr& menu_box,
    bn::sprite_text_generator& text_generator
  ):
    menu_box_(menu_box),
    text_generator_(text_generator)
  {
    
    bn::sprite_items::bg.create_sprite(bn::fixed(0),bn::fixed(0)); 
    bn::sprite_ptr menu_box_ = bn::sprite_items::bg.create_sprite(0,0);
    menu_box_.set_scale(bn::fixed(125) / bn::fixed(64) , bn::fixed(25) / bn::fixed(64));
    menu_box_.set_x(bn::fixed(50));
    menu_box_.set_y(bn::fixed(45));
    menu_box_.set_visible(false);
  }

  void DungeonDialogueMenu::update(){

  }
}
