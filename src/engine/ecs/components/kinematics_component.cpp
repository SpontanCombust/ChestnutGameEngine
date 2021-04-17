#include "kinematics_component.hpp"

namespace chestnut
{
    SKinematicsComponent::SKinematicsComponent()
    {
        velocity = vec2f(0, 0);
        acceleration = vec2f(0, 0);
    }

    SKinematicsComponent::SKinematicsComponent( vec2f _velocity, vec2f _acceleration ) 
    {
        velocity = _velocity;
        acceleration = _acceleration;
    }

} // namespace chestnut
