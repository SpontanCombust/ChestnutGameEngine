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
        
        //TODO create "missing texture" for default constructor
        STextureComponent() = default;
        STextureComponent( CTexture2D _texture );
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__