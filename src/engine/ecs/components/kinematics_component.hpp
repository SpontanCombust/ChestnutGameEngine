#ifndef __CHESTNUT_KINEMATICS_COMPONENT_H__
#define __CHESTNUT_KINEMATICS_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector2.hpp"

namespace chestnut
{
    struct SKinematicsComponent : IComponent
    {
        vec2f linearVelocity;
        vec2f linearAcceleration;
        double angularVelocity;
        double angularAcceleration;

        SKinematicsComponent();
        SKinematicsComponent( vec2f _linearVelocity, vec2f _linearAcceleration );
        SKinematicsComponent( vec2f _linearVelocity, vec2f _linearAcceleration, double _angularVelocity, double _angularAcceleration );
    };

} // namespace chestnut 

#endif // __CHESTNUT_KINEMATICS_COMPONENT_H__