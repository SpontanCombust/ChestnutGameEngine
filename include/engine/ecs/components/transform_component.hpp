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
        STransformComponent( Vector2f _position, Vector2f _rotation, Vector2f _scale );

        static const std::string getTypeStringStatic();
        inline virtual const std::string getTypeString() { return getTypeStringStatic(); };
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__