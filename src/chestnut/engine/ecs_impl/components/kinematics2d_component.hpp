#ifndef __CHESTNUT_ENGINE_KINEMATICS2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_KINEMATICS2D_COMPONENT_H__

#include "../../maths/vector2.hpp"

namespace chestnut::engine
{
    struct CKinematics2DComponent
    {
        vec2f linearVelocity;
        vec2f linearAcceleration;
        float angularVelocity;
        float angularAcceleration;

        CKinematics2DComponent();
    };

} // namespace chestnut::engine 

#endif // __CHESTNUT_ENGINE_KINEMATICS2D_COMPONENT_H__