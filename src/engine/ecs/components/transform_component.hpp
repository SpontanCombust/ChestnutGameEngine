#ifndef __CHESTNUT_TRANSFORM_COMPONENT_H__
#define __CHESTNUT_TRANSFORM_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector2.hpp"

namespace chestnut
{
    struct STransformComponent : IComponent
    {
        vec2f position;
        vec2f scale;
        double rotation;

        STransformComponent();
        STransformComponent( vec2f _position, vec2f _scale, double _rotation );
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__