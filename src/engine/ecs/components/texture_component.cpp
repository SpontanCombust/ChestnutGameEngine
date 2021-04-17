#include "texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent()
    {
        anchor = ETextureAnchor::CENTER;
        scaleOffset = vec2f( 0.f, 0.f );
    }

    STextureComponent::STextureComponent( CTexture textureInstance, ETextureAnchor _anchor, vec2f _scaleOffset )
    : texture( textureInstance )
    {
        anchor = _anchor;
        scaleOffset = _scaleOffset;
    }

} // namespace chestnut
