#pragma once


#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/graphics/sprite.hpp"

namespace chestnut::engine
{
    //TODO maybe it'd be better to move it to Model2DComponent and make it more general 
    // for all components that have to adjust to model size in some way
    enum class ESpriteToModel2DAdjust
    {
        NONE, // texture doesn't adjust to the model
        SCALED, // scale up/down keeping the aspect ratio to fit inside the model
        SPANNED, // scale up/down without keeping the aspect ratio to fit the entire surface area of the model 
        ZOOMED // scale up/down keeping the aspect ratio to fit the entire surface area of the model and possibly going beyond the shape
    };

    struct CSpriteComponent
    {
        CSprite sprite;
        ESpriteToModel2DAdjust adjust = ESpriteToModel2DAdjust::SCALED;
    };

} // namespace chestnut::engine 
