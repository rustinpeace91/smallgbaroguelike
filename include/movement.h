#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "bn_regular_bg_map_item.h"
#include "bn_point.h"
#include <array>

enum class direction { east = 0, north = 1, west = 2, south = 3 };

struct coordinates { 
    int x; 
    int y; 
};

class Movement {
public:
    direction player_direction;
    std::array<int, 4> playerAngles;
    coordinates coords; 
    int valid_tile_index;
    bn::regular_bg_ptr map_bg;
    bn::sprite_ptr dog_sprite;

    Movement(bn::regular_bg_ptr &map_bg, bn::sprite_ptr &dog_sprite);

    int increment_direction(int counter, int step);
    coordinates genereate_new_playerdir(direction d, int movement);
    void debug_logger(int x);
    void update();

private:
    bn::point dog_map_position;
    int player_dir_counter;
    bn::regular_bg_map_item map_item; 
};

#endif // MOVEMENT_H
