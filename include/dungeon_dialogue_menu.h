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

      // make a configurable variable 
      int number_of_lines_ = 2;
      int frame_counter_ = 0;
      int frame_speed_ = 2;

      // UI variables
      // Make parameters?
      int menu_box_width_ = 125;
      int menu_box_height_ = 25;
      // int menu_box_position_x_ = 50;
      int menu_box_position_x_ = 0;
      int menu_box_position_y_ = 45;

      int text_start_x_ = -50;
      int text_start_y_ = 40;
      int text_spacing_ = 10;

      // state variables
      const bn::string_view* current_dialogue_ = nullptr;
      int dialogue_length_ = 0;
      bool is_text_showing_ = false;
      bool is_text_updating_ = false;
      
        // typewriter logic
      int text_line_index_ = 0;
      int current_page_line_character_ = 0;
      int current_page_line_typing_ = 0;
      

  };
}
