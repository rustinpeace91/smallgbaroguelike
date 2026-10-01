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
        // on button press check if dialogue needs to be closed
        //
        //
        // Typewriter logic
        // int text_index = 0;
        // int line1_index
        // int line2_index
        // if(line1_index < line1.length())
        //  only print first line logic
        // else 
        //  print all of first line and index on second line
        //  if(line2_index < line2.length)
        //    is_text_updating = false
        //    button can be pressed again
        //      on button press: text_index +=2?
        //
        if(!is_text_updating_)
        {
            // Is the current page the last page?
            if(text_index_ + 2 >= dialogue_length_)
            {
                dialogue_text_sprites_.clear();
                text_index_ = 0;                
                line1_index_ = 0;
                line2_index_ = 0;
                is_text_showing_ = false;
                is_text_updating_ = false;
                menu_box_.set_visible(false);
            }
            else
            {
                text_index_ += 2;
                dialogue_text_sprites_.clear();
                is_text_updating_ = true;

                line1_index_ = 0;
                line2_index_ = 0;
                frame_counter_ = 0;
            }
        }
      }
    }

    // End of A press (stupid text editor)
    if(is_text_updating_ && text_index_ < dialogue_length_){

        frame_counter_++;
        // handle all update logic here
        if(frame_counter_ % frame_speed_ == 0){
          if(line1_index_ < current_dialogue_[text_index_].length()){
            line1_index_++;
          } else if(
            dialogue_length_ > text_index_ + 1 &&
            line2_index_ < current_dialogue_[text_index_ + 1].length()
          ){
            line2_index_++;
          } else {
            is_text_updating_ = false;
          }
        }
        // just print the text
        // clear previous text?
        dialogue_text_sprites_.clear();
        text_generator_.generate(
          bn::fixed(0), 
          bn::fixed(40),
          bn::string_view(current_dialogue_[text_index_].substr(0, line1_index_)),
          dialogue_text_sprites_
        );
        // do we need this? think 
        menu_box_.set_visible(true);
        if(dialogue_length_ > text_index_ + 1){
          text_generator_.generate(
            bn::fixed(0),
            bn::fixed(50), 
            bn::string_view(current_dialogue_[text_index_ + 1].substr(0, line2_index_)),
            dialogue_text_sprites_
          );
          // text_index_++;
        }

    }
  }
}
