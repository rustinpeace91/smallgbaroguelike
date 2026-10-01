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
    menu_box_.set_scale(bn::fixed(125) / bn::fixed(64) , bn::fixed(25) / bn::fixed(64));
    menu_box_.set_x(bn::fixed(50));
    menu_box_.set_y(bn::fixed(45));
    menu_box_.set_visible(false);
  }

  void DungeonDialogueMenu::update(){
    if (bn::keypad::a_pressed())
    {

      // first time opening text
      if(!is_text_showing_){

        BN_LOG("Sprites used: ", bn::sprites::used_items_count());
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
                current_textbox_index_ = 0;
            }
            else
            {
                text_line_index_ += number_of_lines_;
                dialogue_text_sprites_.clear();
                is_text_updating_ = true;
                frame_counter_ = 0;
                current_textbox_index_ = 0;
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
        current_textbox_index_++;
        int characters_remaining = current_textbox_index_; 
        for(int i = 0; i < number_of_lines_; i++){
          // are we on the last page?
          if(text_line_index_ + i > dialogue_length_){
            is_text_updating_ = false;
            // next A press will clear the page
            break;
          } else if(
            characters_remaining > current_dialogue_[text_line_index_ + i].length()
          ) {
            // if current_line_index_ is greater than length of line, print whole line
            text_generator_.generate(
              bn::fixed(0),
              bn::fixed(40 + i * 10), 
              current_dialogue_[text_line_index_ + i],
              dialogue_text_sprites_
            );
            characters_remaining -= current_dialogue_[text_line_index_ + i].length();

          } else {  
            text_generator_.generate(
              bn::fixed(0),
              bn::fixed(40 + i * 10), 
              current_dialogue_[text_line_index_ + i].substr(
                0,
                characters_remaining
              ),
              dialogue_text_sprites_
            );
          };
        }
      }
    }
  }
}
