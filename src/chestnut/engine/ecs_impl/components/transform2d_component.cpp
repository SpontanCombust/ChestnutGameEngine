#include "transform2d_component.hpp"

namespace chestnut::engine
{
    CTransform2DComponent::CTransform2DComponent()
    {
        position = vec2f(0.f);
        scale = vec2f(1.f);
        rotation = 0.f;
    }

} // namespace chestnut::engine
