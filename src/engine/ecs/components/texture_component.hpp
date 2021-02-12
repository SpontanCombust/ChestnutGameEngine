#ifndef __CHESTNUT_TEXTURE_COMPONENT_H__
#define __CHESTNUT_TEXTURE_COMPONENT_H__

#include "../component.hpp"
#include "engine/graphics/texture.hpp"

namespace chestnut
{
    enum class ETextureAnchor
    {
        UPPER_LEFT, UP,     UPPER_RIGHT,
        LEFT,       CENTER, RIGHT,
        LOWER_LEFT, DOWN,   LOWER_RIGHT
    };

    struct STextureComponent : IComponent
    {
        CTexture texture;
        
        ETextureAnchor anchor;
        Vector2f scaleOffset;

        //TODO create "missing texture" for default constructor
        STextureComponent();
        STextureComponent( CTexture textureInstance, ETextureAnchor _anchor = ETextureAnchor::CENTER, Vector2f _scaleOffset = Vector2f( 0.f, 0.f ) );
    };

} // namespace chestnut 


#endif // __CHESTNUT_TEXTURE_COMPONENT_H__