#include "engine/ecs/components/kinematics_component.hpp"

namespace chestnut
{
    SKinematicsComponent::SKinematicsComponent()
    : velocity( {0, 0} ), acceleration( {0, 0} )
    {

    }

    const std::string SKinematicsComponent::getTypeStatic()
    {
        return "kinematics";
    }
    
} // namespace chestnut
