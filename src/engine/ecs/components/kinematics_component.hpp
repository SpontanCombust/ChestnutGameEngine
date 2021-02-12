#ifndef __CHESTNUT_KINEMATICS_COMPONENT_H__
#define __CHESTNUT_KINEMATICS_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector.hpp"

namespace chestnut
{
    struct SKinematicsComponent : IComponent
    {
        Vector2f velocity;
        Vector2f acceleration;

        SKinematicsComponent();
        SKinematicsComponent( Vector2f _velocity, Vector2f _acceleration );
    };

} // namespace chestnut 

#endif // __CHESTNUT_KINEMATICS_COMPONENT_H__