
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_unique_ptr.h"
#include "bn_sprite_text_generator.h"

// #include "bn_sprite_text_generator.h"
// #include "bn_regular_bg_map_cell_info.h"
//
#include "dungeon_scene.h"
#include "dungeon_scene_type.h"
#include "dungeon_overworld.h"
#include "dungeon_player_menu.h"
#include "dungeon_game_state.h"
#include "common_variable_8x16_sprite_font.h"


//------TEXBOX IMPORTS --------
#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_menuarrow.h"
#include "dummy_data.h"


// generate_text("fuck you fuuuuu /n")

void update_textbox_text(
  const bn::string_view text[],
  int length,
  bn::sprite_text_generator& text_generator_,
  bn::vector<bn::sprite_ptr, 64>& dialogue_text_sprites_, // Fixed typo: vector holds sprite_ptr, not sprite_ptr&
  int& text_index,            // Passed by reference
  bool& is_text_showing,      // Passed by reference
  bool& is_text_updating,      // Passed by reference
  bn::sprite_ptr& menu_box_
){
  if(is_text_showing){
    if(length > text_index){
      // show text
      if(is_text_updating){
        text_generator_.generate(
          bn::fixed(0), 
          bn::fixed(40),
          bn::string_view(text[text_index]),
          dialogue_text_sprites_
        );
        menu_box_.set_visible(true);
        // show next line if exists
        if(length > text_index + 1){
          text_generator_.generate(
            bn::fixed(0),
            bn::fixed(50),
            bn::string_view(text[text_index + 1]),
            dialogue_text_sprites_
          );
          text_index++;
        }
        is_text_updating = false;
      }
      else if (bn::keypad::a_pressed())
      {
      // input increases text index
      // clear text_generato
        text_index++;
        dialogue_text_sprites_.clear();
        is_text_updating = true;
      }

      // regenerate_text
    } else {
      dialogue_text_sprites_.clear();
      text_index = 0;
      // clear text_generator
      //set isTextShowing to false
      is_text_showing = false;
      is_text_updating = false;
      menu_box_.set_visible(false);
    }
    // clear menu box?
  }
}
int main()
{
    dungeon::GameState game_state;
    bn::core::init();

    // text,assets etc. will go here

    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    // assets end
    bn::unique_ptr<dungeon::Scene> scene(
        new dungeon::Overworld(game_state)
    );

    bn::optional<dungeon::scene_type> next_scene = dungeon::scene_type::OVERWORLD;

    // ------TEXBOX VARIABLES------ MOVE TO CLASS
    bn::sprite_items::bg.create_sprite(bn::fixed(0),bn::fixed(0)); 
    bn::vector<bn::sprite_ptr, 64> dialogue_text_sprites_;

    // move this out
    int MAX_TEXT_LINES = 2;
    int text_index = 0;
    const bn::string_view* current_dialogue = nullptr;
    int dialogue_length = 0;
    bool is_text_showing = false;
    // for typewriter effect later
    bool is_text_updating = false;
    bn::sprite_ptr menu_box_ = bn::sprite_items::bg.create_sprite(0,0);
    menu_box_.set_scale(bn::fixed(125) / bn::fixed(64) , bn::fixed(25) / bn::fixed(64));
    menu_box_.set_x(bn::fixed(50));
    menu_box_.set_y(bn::fixed(45));
    menu_box_.set_visible(false);
    // ------- END TEXTBOX VARIABLES ------//

    while(true){
        // textbox setup
        if (bn::keypad::a_pressed() && !is_text_showing)
        {
          static const bn::string_view test_dialogue[] = {
              "This is a dialogue",
              "Box example",
              "This is what it do"
          };
          current_dialogue = test_dialogue;
          dialogue_length = 3;
          is_text_showing = true;
          is_text_updating = true;
        }
        update_textbox_text(
          current_dialogue,
          dialogue_length,
          text_generator,
          dialogue_text_sprites_,
          text_index,
          is_text_showing,
          is_text_updating,
          menu_box_
        );



        if(scene){
            next_scene = scene->update();
        }
        // if no next_scene, just keep going
        //
        if(next_scene){
            // scene change logic will go here, 
            // switch statement on next_scene
            switch(*next_scene){
                case dungeon::scene_type::OVERWORLD:
                    scene.reset(new dungeon::Overworld(game_state));
                    break;
                case dungeon::scene_type::MENU:
                    scene.reset(new dungeon::PlayerMenu(text_generator));
                    break;
                default:
                    break;
            }
            // smart pointer (?) owernship will change here
        }

        bn::core::update();
    };

}
