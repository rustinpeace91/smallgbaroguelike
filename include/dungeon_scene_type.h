/* More code lifted from the butano fighter example. seems like a sensible solution to scene management */

/*
 * Copyright (c) 2020-2026 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef DUNGEON_SCENE_TYPE_H
#define DUNGEON_SCENE_TYPE_H

#include "bn_common.h"

namespace dungeon
{
    enum class scene_type
    {
        OVERWORLD,
        MENU
    };
}

#endif
