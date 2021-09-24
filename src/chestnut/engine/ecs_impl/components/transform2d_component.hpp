#ifndef __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__

#include "../../maths/vector2.hpp"

#include <chestnut/ecs/component.hpp>

namespace chestnut
{
    struct CTransform2DComponent : public ecs::CComponent
    {
        vec2f position;
        vec2f scale;
        float rotation;

        CTransform2DComponent();
    };

} // namespace chestnut 

#endif // __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__