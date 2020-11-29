#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent()
    {
        anchor = ETextureAnchor::CENTER;
        scaleOffset = Vector2f( 0.f, 0.f );
    }

    STextureComponent::STextureComponent( CTexture textureInstance, ETextureAnchor _anchor, Vector2f _scaleOffset )
    : texture( textureInstance )
    {
        anchor = _anchor;
        scaleOffset = _scaleOffset;
    }

} // namespace chestnut
