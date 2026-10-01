#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"

namespace dungeon{
  class DungeonDialogueMenu
  {
    public:
      DungeonDialogueMenu(
        // bn::sprite_ptr& menu_box,
        bn::sprite_text_generator& text_generator
      );
      void update();
    private:
    
      // handle this in intializer 
      bn::sprite_ptr menu_box_;
      bn::sprite_text_generator text_generator_;
      // // ------TEXBOX VARIABLES------ MOVE TO CLASS
      bn::vector<bn::sprite_ptr, 64> dialogue_text_sprites_;

      // typewriter logic
      int text_line_index_ = 0;
      int current_textbox_index_=0;
      // make a configurable variable 
      int number_of_lines_ = 2;
      // TODO: Does not scale well
      // int line1_index_ = 0;
      // int line2_index_ = 0;
      //
      int frame_counter_ = 0;
      int frame_speed_ = 2;

      const bn::string_view* current_dialogue_ = nullptr;
      int dialogue_length_ = 0;
      bool is_text_showing_ = false;
      // // for typewriter effect later
      bool is_text_updating_ = false;
      // bn::sprite_items::bg.create_sprite(bn::fixed(0),bn::fixed(0)); 
      // bn::sprite_ptr menu_box_ = bn::sprite_items::bg.create_sprite(0,0);
      // menu_box_.set_scale(bn::fixed(125) / bn::fixed(64) , bn::fixed(25) / bn::fixed(64));
      // menu_box_.set_x(bn::fixed(50));
      // menu_box_.set_y(bn::fixed(45));
      // menu_box_.set_visible(false);
  };
}
