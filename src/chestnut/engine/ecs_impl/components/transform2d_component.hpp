#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CTransform2DComponent
    {
        vec2f position;
        vec2f scale;
        float rotation;

        CTransform2DComponent();
    };

} // namespace chestnut::engine 
