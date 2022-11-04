#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    struct CKinematics2DComponent
    {
        vec2f linearVelocity;
        vec2f linearAcceleration;
        float angularVelocity;
        float angularAcceleration;

        CKinematics2DComponent()
        {
            linearVelocity = vec2f(0.f);
            linearAcceleration = vec2f(0.f);
            angularVelocity = 0.f;
            angularAcceleration = 0.f;
        }
    };

} // namespace chestnut::engine 
