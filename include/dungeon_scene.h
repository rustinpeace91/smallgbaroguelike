/*lifted directly from the butano fighter codebase*/

/*
 * Copyright (c) 2020-2026 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef DUNGEON_SCENE_H
#define DUNGEON_SCENE_H

#include "bn_optional.h"

namespace dungeon
{

enum class scene_type;

class Scene
{

public:
    virtual ~Scene() = default;

    [[nodiscard]] virtual bn::optional<scene_type> update() = 0;

protected:
    Scene() = default;
};

}

#endif
