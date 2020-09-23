#include "engine/ecs/components/texture_component.hpp"

namespace chestnut
{
    STextureComponent::STextureComponent()
    : texture(nullptr)
    {

    }

    const std::string STextureComponent::getTypeStatic()
    {
        return "texture";
    }

} // namespace chestnut
