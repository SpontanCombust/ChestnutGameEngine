#ifndef __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__

#include "chestnut/engine/macros.hpp"
#include "../../maths/vector2.hpp"

namespace chestnut::engine
{
    struct CHESTNUT_API CTransform2DComponent
    {
        vec2f position;
        vec2f scale;
        float rotation;

        CTransform2DComponent();
    };

} // namespace chestnut::engine 

#endif // __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__