#ifndef __CHESTNUT_TRANSFORM_COMPONENT_H__
#define __CHESTNUT_TRANSFORM_COMPONENT_H__

#include "engine/ecs/component.hpp"
#include "engine/core/vector.hpp"

namespace chestnut
{
    struct STransformComponent : SComponent
    {
        Vector2f position;
        Vector2f rotation;
        Vector2f scale;

        STransformComponent();

        static const std::string getTypeStatic();
        inline virtual const std::string getType() { return getTypeStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__