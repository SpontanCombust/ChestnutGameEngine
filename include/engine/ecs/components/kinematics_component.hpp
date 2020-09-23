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

        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_KINEMATICS_COMPONENT_H__