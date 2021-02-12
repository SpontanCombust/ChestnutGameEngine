#ifndef __CHESTNUT_TRANSFORM_COMPONENT_H__
#define __CHESTNUT_TRANSFORM_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector.hpp"

namespace chestnut
{
    struct STransformComponent : IComponent
    {
        Vector2f position;
        Vector2f rotation;
        Vector2f scale;

        STransformComponent();
        STransformComponent( Vector2f _position, Vector2f _rotation, Vector2f _scale );
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__