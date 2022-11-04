#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CKinematics2DComponent
    {
        vec2f linearVelocity;
        vec2f linearAcceleration;
        float angularVelocity;
        float angularAcceleration;

        CKinematics2DComponent();
    };

} // namespace chestnut::engine 
