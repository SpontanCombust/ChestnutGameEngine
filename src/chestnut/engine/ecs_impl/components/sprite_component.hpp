#pragma once

#include "chestnut/engine/macros.hpp"
#include "../../maths/vector2.hpp"
#include "../../graphics/sprite.hpp"

namespace chestnut::engine
{
    enum class ESpriteToModel2DAdjust
    {
        NONE, // texture doesn't adjust to the model
        SCALED, // scale up/down keeping the aspect ratio to fit inside the model
        SPANNED, // scale up/down without keeping the aspect ratio to fit the entire surface area of the model 
        ZOOMED // scale up/down keeping the aspect ratio to fit the entire surface area of the model and possibly going beyond the shape
    };

    struct CHESTNUT_API CSpriteComponent
    {
        CSprite sprite;
        ESpriteToModel2DAdjust adjust;

        CSpriteComponent();
    };

} // namespace chestnut::engine 
