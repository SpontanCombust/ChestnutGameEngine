#include "transform_component.hpp"

namespace chestnut
{
    CTransformComponent::CTransformComponent()
    {
        position = vec2f(0.f);
        scale = vec2f(1.f);
        rotation = 0.f;
    }

} // namespace chestnut
