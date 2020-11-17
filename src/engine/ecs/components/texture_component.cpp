#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent()
    : texture( nullptr )
    {

    }

    STextureComponent::STextureComponent( CTexture *textureInstance )
    : texture( textureInstance )
    {

    }

} // namespace chestnut
