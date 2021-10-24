#ifndef __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__

#include "../../maths/vector2.hpp"
#include "../../graphics/texture2d.hpp"

namespace chestnut::engine
{
    struct CTextureComponent
    {
        CTexture2D texture;
        vec2f origin; // values typically in range (0;1) where 0 = left/top and 1 = right/bottom
        
        CTextureComponent() = default;
    };

} // namespace chestnut::engine 

#endif // __CHESTNUT_ENGINE_TEXTURE2D_COMPONENT_H__