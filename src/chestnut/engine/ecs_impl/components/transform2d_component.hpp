#pragma once


#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    struct CTransform2DComponent
    {
        vec2f position = {0.f, 0.f};
        vec2f scale = {1.f, 1.f};
        float rotation = 0.f;
    };

} // namespace chestnut::engine 
