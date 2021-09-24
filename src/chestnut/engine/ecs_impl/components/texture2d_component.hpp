#ifndef __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__

#include "../../maths/vector2.hpp"
#include "../../graphics/texture2d.hpp"

#include <chestnut/ecs/component.hpp>

namespace chestnut
{
    struct CTextureComponent : public ecs::CComponent
    {
        CTexture2D texture;
        vec2f origin; // values typically in range (0;1) where 0 = left/top and 1 = right/bottom
        
        //TODO create "missing texture" for default constructor
        CTextureComponent() = default;
    };

} // namespace chestnut 

#endif // __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__