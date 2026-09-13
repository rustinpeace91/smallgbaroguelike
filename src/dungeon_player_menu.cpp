#include "dungeon_player_menu.h"
#include "dungeon_scene_type.h"
#include "bn_sprite_text_generator.h"

#include "bn_sprite_items_bg.h"
#include "bn_sprite_items_dog.h"
#include "bn_sprite_items_knight.h"
#include "bn_sprite_items_menuarrow.h"
#include "bn_regular_bg_items_map.h"
#include "bn_log.h"

#include "dummy_data.h"

namespace dungeon {


// Use the constructor initialization list to set your private variable
PlayerMenu::PlayerMenu(bn::sprite_text_generator& text_generator)
    : Scene(),
      text_generator_(text_generator),
      menu_box_(bn::sprite_items::bg.create_sprite(0, 0)),
      menu_arrow_(bn::sprite_items::menuarrow.create_sprite(0, 0)),
      up_arrow_(bn::sprite_items::menuarrow.create_sprite(0, 0)),
      down_arrow_(bn::sprite_items::menuarrow.create_sprite(0, 0)),
      menu_mode_(PlayerMenu::menu_options::MAIN_MENU)
{
  menu_box_.set_position(0 + (120 - (menu_width_ / 2)),
                        0 + (80 - (menu_height_ / 2)));
  horizontal_scale_ = bn::fixed(menu_width_) / 64;
  vertical_scale_ = bn::fixed(menu_height_) / 64;
  menu_box_.set_scale(horizontal_scale_, vertical_scale_);
  menu_box_.set_visible(true);

  up_arrow_.set_x(bn::fixed(60));
  up_arrow_.set_y(bn::fixed(-10));
  down_arrow_.set_x(bn::fixed(60));
  down_arrow_.set_y(bn::fixed(72));
  menu_arrow_.set_visible(false);
  up_arrow_.set_visible(false);
  down_arrow_.set_visible(false);
  intiate_main_menu();

}

void PlayerMenu::generate_inventory_menu_text(

    int page_start,
    int page_end
){
    // paginate
    // DummyData::INVENTORY
    //

    int text_start_x = 55;
    int text_start_y = 0;

    int text_x = text_start_x;
    int text_y = text_start_y;
    for(int i =page_start; i< page_end and i < std::ssize(DummyData::INVENTORY); i++){
        text_generator_.generate(
            text_x,
            text_y,
            bn::string_view(DummyData::INVENTORY[i]),
            menu_text_sprites_
        );
        text_y += 20;
    }
};


void PlayerMenu::generate_menu_text()
{
    int text_start_x = 55;
    int text_start_y = 0;

    int text_x = text_start_x;
    int text_y = text_start_y;

    for(const char* option : DummyData::MAIN_MENU_OPTIONS)
    {
        text_generator_.generate(
            text_x,
            text_y,
            bn::string_view(option),
            menu_text_sprites_
        );

        text_y += 20;
    }
}

void PlayerMenu::handle_arrow_display() {
    if(page_start_ > 0){
        up_arrow_.set_visible(true);
    } else {
        up_arrow_.set_visible(false);
    }
    if(page_end_ < menu_item_total_){
        down_arrow_.set_visible(true);
    } else {
        down_arrow_.set_visible(false);
    }
}

void PlayerMenu::intiate_main_menu() {
    menu_mode_ = menu_options::MAIN_MENU;
    menu_size_ = 4;
    menu_text_sprites_.clear();
    generate_menu_text();
    menu_box_.set_visible(true);
    menu_arrow_.set_visible(true);
    up_arrow_.set_visible(false);
    down_arrow_.set_visible(false); 
}

bn::optional<dungeon::scene_type> PlayerMenu::update() {
    // Your update logic here
    if (bn::keypad::b_pressed()) {
        return dungeon::scene_type::OVERWORLD;
    }

    if(bn::keypad::a_pressed() && menu_mode_ == menu_options::MAIN_MENU)
    {
        if(menu_position_index_ == static_cast<int>(menu_mode_ == menu_options::INVENTORY_MENU)){
            menu_position_index_ = 0;
            menu_mode_ = menu_options::INVENTORY_MENU;
            menu_size_ = std::ssize(DummyData::MAIN_MENU_OPTIONS);

            menu_text_sprites_.clear();

            // menu_box.set_visible(false);
            // reset arrow
            // max_page_size = 0;
            page_start_ = 0;
            menu_item_total_ = std::ssize(DummyData::INVENTORY);
            if(menu_item_total_ < max_page_size_){
                page_end_ = menu_item_total_;
            } else {
                down_arrow_.set_visible(true);
                page_end_ = max_page_size_;
            };
            menu_text_sprites_.clear();
            generate_inventory_menu_text(
                page_start_,
                page_end_
            );
            handle_arrow_display();

        }
    }
    if(bn::keypad::up_pressed()){
        if(menu_mode_ == menu_options::INVENTORY_MENU){
            if(
                // scroll to end of menu, but more items
                (menu_position_index_ == 0) && 
                (page_start_ > 0)
            ){
                page_start_ = page_start_ - max_page_size_;
                if(menu_item_total_ < max_page_size_){
                    page_end_ = menu_item_total_;
                } else { 
                    page_end_ = page_start_ + max_page_size_;
                };
                if(page_start_ < 0){page_start_ = 0;};
                menu_position_index_ = 0;
                menu_text_sprites_.clear();
                generate_inventory_menu_text(
                    page_start_,
                    page_end_
                );
                handle_arrow_display();
            }
        }
        if(menu_position_index_ > 0){
            menu_position_index_--;
        }
    }
    if(bn::keypad::down_pressed()){
        BN_LOG("Current Value of Menu Index:");
        BN_LOG(menu_position_index_);
        if(menu_mode_ == menu_options::INVENTORY_MENU){
            if(
                // scroll to end of menu, but more items
                (menu_position_index_ >= max_page_size_ - 1) && 
                (page_start_ + max_page_size_ < menu_item_total_)
            ){
                page_start_ = page_start_ + max_page_size_;

                if(menu_item_total_ < page_start_ + max_page_size_){
                    page_end_ = menu_item_total_;
                } else { 
                    page_end_ = page_start_ + max_page_size_;
                };
                menu_position_index_ = 0;
                menu_text_sprites_.clear();
                generate_inventory_menu_text(
                    page_start_,
                    page_end_
                );
                handle_arrow_display();

            } else {
                int current_page_size = page_end_ - page_start_;
                if(menu_position_index_ < current_page_size - 1){
                    menu_position_index_++;
                }
            }
        } else {

            if(menu_position_index_ < menu_size_ - 1){
                menu_position_index_++;
            }
        }
    }

  menu_arrow_.set_x(bn::fixed(arrow_position_x_));
  menu_arrow_.set_y(bn::fixed(arrow_position_y_  + 20 * (menu_position_index_ + 1)));


  return bn::nullopt;
}

} // namespace dungeon
