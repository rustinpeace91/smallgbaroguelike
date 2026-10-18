#include "bn_sprite_text_generator.h"
#include "bn_sprites.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "dungeon_dialogue_menu.h"

//------TEXBOX IMPORTS --------
#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_menuarrow.h"
#include "dummy_data.h"
#include "bn_log.h"

namespace dungeon{
  DungeonDialogueMenu::DungeonDialogueMenu(
    // bn::sprite_ptr& menu_box,
    bn::sprite_text_generator& text_generator
  ):
    // menu_box_(menu_box),
    menu_box_(bn::sprite_items::bg.create_sprite(0, 0)),
    text_generator_(text_generator)
  {
    
    // bn::sprite_items::bg.create_sprite(bn::fixed(0),bn::fixed(0)); 
    // menu_box_ = bn::sprite_items::bg.create_sprite(0,0);
    menu_box_.set_scale(bn::fixed(menu_box_width_) / bn::fixed(64) , bn::fixed(menu_box_height_) / bn::fixed(64));
    menu_box_.set_x(bn::fixed(menu_box_position_x_));
    menu_box_.set_y(bn::fixed(menu_box_position_y_));
    menu_box_.set_visible(false);
  }

  void DungeonDialogueMenu::update(){
    if (bn::keypad::a_pressed())
    {

      // first time opening text
      if(!is_text_showing_){

        BN_LOG("Sprites used: ", bn::sprites::used_items_count());
        /// TODO: move this outta hea
        static const bn::string_view test_dialogue[] = {
            "This is dialogue",
            "Box example",
            "This is what it do"
        };
        current_dialogue_ = test_dialogue;
        dialogue_length_ = 3;
        frame_counter_ = 0;
        is_text_showing_ = true;
        is_text_updating_ = true;
        menu_box_.set_visible(true);
      } else {
        if(!is_text_updating_)
        {
            // Is the current page the last page?
            if(text_line_index_ + number_of_lines_ >= dialogue_length_)
            {
                dialogue_text_sprites_.clear();
                text_line_index_ = 0;
                is_text_showing_ = false;
                is_text_updating_ = false;
                menu_box_.set_visible(false);
                frame_counter_ = 0;
                current_page_line_character_ = 0;
                current_page_line_typing_ = 0;
            }
            else
            {
                text_line_index_ += number_of_lines_;
                dialogue_text_sprites_.clear();
                is_text_updating_ = true;
                frame_counter_ = 0;
                current_page_line_character_ = 0;
                current_page_line_typing_ = 0;
            }
        }
      }
    }

    // End of A press (stupid text editor)

    if(is_text_updating_ && text_line_index_ < dialogue_length_){
      frame_counter_++;
      if(frame_counter_ % frame_speed_ == 0){
        // clear out old sprites
        dialogue_text_sprites_.clear();
        for(int i=0; i < number_of_lines_; i++){
          if(
              text_line_index_ + i < dialogue_length_ &&
              i < current_page_line_typing_
          ){
            //type full line

            text_generator_.generate(
              bn::fixed(text_start_x_),
              bn::fixed(text_start_y_ + i * text_spacing_), 
              current_dialogue_[text_line_index_ + i],
              dialogue_text_sprites_
            );
          } else if (
            text_line_index_ + i < dialogue_length_ &&
            i == current_page_line_typing_
          ){
            bn:: string_view current_line_string = current_dialogue_[text_line_index_ + i];
            // type substring of line
            text_generator_.generate(
              bn::fixed(text_start_x_),
              bn::fixed(text_start_y_ + i * text_spacing_), 
              current_line_string.substr(
                0,
                current_page_line_character_
              ),
              dialogue_text_sprites_
            );
            current_page_line_character_++;
            // check if we need to advance line
            if(
              current_page_line_character_ > current_line_string.length()
            ){
              current_page_line_character_ = 0;
              current_page_line_typing_++;
              // check if we need to advance page
              if(current_page_line_typing_ >= number_of_lines_ || text_line_index_ + current_page_line_typing_ >= dialogue_length_){
                is_text_updating_=false;
                // will stop text from updating and prompt for A press
                // which will determine to move onto next page or close box
                break;
              }
            }
          } 
        }
      }
    }
  }
}
