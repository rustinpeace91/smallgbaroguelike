#ifndef DUNGEON_PLAYER_MENU_H
#define DUNGEON_PLAYER_MENU_H

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_map_cell_info.h"

#include "dungeon_scene.h"
#include <array>

namespace dungeon
{
    class PlayerMenu : public Scene
    {
    public:
        PlayerMenu(bn::sprite_text_generator& text_generator);
        bn::optional<scene_type> update() override;

      private:
        enum class menu_options
        {
            MAIN_MENU,
            INVENTORY_MENU,
            OPTIONS_MENU,
            MAGIC_MENU
        };

        // assets
        bn::sprite_text_generator text_generator_;
        bn::sprite_ptr menu_box_;
        bn::sprite_ptr menu_arrow_;
        bn::sprite_ptr up_arrow_;
        bn::sprite_ptr down_arrow_;
        bn::vector<bn::sprite_ptr, 64> menu_text_sprites_;
        menu_options menu_mode_;


        int menu_size_;
        // TODO: make these constants
        int menu_width_ = 75;
        int menu_height_ = 100;
        int arrow_position_x_ = 50;
        int arrow_reset_ = 0;
        int arrow_position_y_ = -20;
        int menu_position_index_ = 0;
        bn::fixed horizontal_scale_ = bn::fixed(menu_width_) / 64;
        bn::fixed vertical_scale_ = bn::fixed(menu_height_) / 64;

        // INVENTORY SCROLLABLE STUFF
        int max_page_size_ = 4;
        int page_start_ = 0;
        int page_end_ = 0;
        int menu_item_total_ = 0;

        void generate_inventory_menu_text(
            int page_start,
            int page_end
        );
        void handle_arrow_display();



    };

}
#endif
