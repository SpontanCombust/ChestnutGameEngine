#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent( CTexture *textureInstance )
    : texture(textureInstance)
    {

    }

    const std::string STextureComponent::getTypeStringStatic()
    {
        return "texture";
    }

} // namespace chestnut
