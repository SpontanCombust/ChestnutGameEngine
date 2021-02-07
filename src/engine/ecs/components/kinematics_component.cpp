#include "kinematics_component.hpp"

namespace chestnut
{
    SKinematicsComponent::SKinematicsComponent()
    : velocity( {0, 0} ), acceleration( {0, 0} )
    {

    }

    SKinematicsComponent::SKinematicsComponent( Vector2f _velocity, Vector2f _acceleration ) 
    : velocity( _velocity ), acceleration( _acceleration )
    {

    }

} // namespace chestnut
