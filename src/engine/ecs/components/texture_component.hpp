#ifndef __CHESTNUT_TEXTURE_COMPONENT_H__
#define __CHESTNUT_TEXTURE_COMPONENT_H__

#include "../component.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/graphics/texture2d.hpp"

namespace chestnut
{
    struct STextureComponent : IComponent
    {
        CTexture2D texture;
        vec2f origin; // values typically in range (0;1) where 0 = left/top and 1 = right/bottom
        
        //TODO create "missing texture" for default constructor
        STextureComponent() = default;
        STextureComponent( CTexture2D _texture );
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__