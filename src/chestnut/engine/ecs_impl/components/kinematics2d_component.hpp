#pragma once


#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    struct CKinematics2DComponent
    {
        vec2f linearVelocity = vec2f(0.f);
        vec2f linearAcceleration = vec2f(0.f);
        float angularVelocity = 0.f;
        float angularAcceleration = 0.f;
    };

} // namespace chestnut::engine 
