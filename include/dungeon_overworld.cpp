#include "dungeon_overworld.h"

namespace dungeon
{

    Overworld::Overworld() : Scene()
    {
        valid_tile_index_ = bn::regular_bg_map_cell_info(valid_map_cell_).tile_index();
    }

    bn::optional<scene_type> Overworld::update()
    {

        // Do the stuff
        return bn::nullopt;
    }

}