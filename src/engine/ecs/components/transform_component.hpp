#ifndef __CHESTNUT_TRANSFORM_COMPONENT_H__
#define __CHESTNUT_TRANSFORM_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector2.hpp"

namespace chestnut
{
    struct STransformComponent : IComponent
    {
        vec2f position;
        vec2f rotation;
        vec2f scale;

        STransformComponent();
        STransformComponent( vec2f _position, vec2f _rotation, vec2f _scale );
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__