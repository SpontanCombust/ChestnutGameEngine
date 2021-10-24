#ifndef __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__

#include "../../maths/vector2.hpp"

namespace chestnut::engine
{
    struct CTransform2DComponent
    {
        vec2f position;
        vec2f scale;
        float rotation;

        CTransform2DComponent();
    };

} // namespace chestnut::engine 

#endif // __CHESTNUT_ENGINE_TRANSFORM2D_COMPONENT_H__