#ifndef DUNGEON_GAME_STATE_H
#define DUNGEON_GAME_STATE_H

namespace dungeon {
class GameState
{
public:

    struct PlayerState
    {
        int x=16;
        int y=16;
        int facing_dir=0;
        // std::string map;

        // int hp;
        // int max_hp;
        // int mp;
        // int max_mp;

        // int level;
        // int experience;
        // int gold;
    };

    PlayerState player;
};

}
#endif