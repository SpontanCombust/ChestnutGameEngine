#ifndef __CHESTNUT_TRANSFORM_COMPONENT_H__
#define __CHESTNUT_TRANSFORM_COMPONENT_H__

#include "../../maths/vector2.hpp"

#include <chestnut/ecs/component.hpp>

namespace chestnut
{
    struct CTransformComponent : public ecs::CComponent
    {
        vec2f position;
        vec2f scale;
        float rotation;

        CTransformComponent();
    };

} // namespace chestnut 

#endif // __CHESTNUT_TRANSFORM_COMPONENT_H__