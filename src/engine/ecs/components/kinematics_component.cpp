#include "kinematics_component.hpp"

namespace chestnut
{
    SKinematicsComponent::SKinematicsComponent()
    {
        linearVelocity = vec2f(0, 0);
        linearAcceleration = vec2f(0, 0);
        angularVelocity = 0;
        angularAcceleration = 0;
    }

    SKinematicsComponent::SKinematicsComponent( vec2f _linearVelocity, vec2f _linearAcceleration ) 
    {
        linearVelocity = _linearVelocity;
        linearAcceleration = _linearAcceleration;
        angularVelocity = 0;
        angularAcceleration = 0;
    }

    SKinematicsComponent::SKinematicsComponent( vec2f _linearVelocity, vec2f _linearAcceleration, double _angularVelocity, double _angularAcceleration ) 
    {
        linearVelocity = _linearVelocity;
        linearAcceleration = _linearAcceleration;
        angularVelocity = _angularVelocity;
        angularAcceleration = _angularAcceleration;
    }

} // namespace chestnut
