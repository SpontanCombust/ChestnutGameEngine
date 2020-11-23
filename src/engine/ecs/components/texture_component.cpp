#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent()
    {

    }

    STextureComponent::STextureComponent( CTexture textureInstance )
    : texture( textureInstance )
    {

    }

} // namespace chestnut
