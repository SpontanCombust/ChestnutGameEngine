#ifndef __CHESTNUT_KINEMATICS_COMPONENT_H__
#define __CHESTNUT_KINEMATICS_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector2.hpp"

namespace chestnut
{
    struct SKinematicsComponent : IComponent
    {
        vec2f velocity;
        vec2f acceleration;

        SKinematicsComponent();
        SKinematicsComponent( vec2f _velocity, vec2f _acceleration );
    };

} // namespace chestnut 

#endif // __CHESTNUT_KINEMATICS_COMPONENT_H__