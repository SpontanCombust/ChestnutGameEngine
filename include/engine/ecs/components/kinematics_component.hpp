#ifndef __CHESTNUT_KINEMATICS_COMPONENT_H__
#define __CHESTNUT_KINEMATICS_COMPONENT_H__

#include "engine/ecs/component.hpp"
#include "engine/core/vector.hpp"

namespace chestnut
{
    struct SKinematicsComponent : SComponent
    {
        Vector2f velocity;
        Vector2f acceleration;

        SKinematicsComponent();
        SKinematicsComponent( Vector2f _velocity, Vector2f _acceleration );

        static const std::string getTypeStringStatic();
        inline virtual const std::string getTypeString() { return getTypeStringStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_KINEMATICS_COMPONENT_H__