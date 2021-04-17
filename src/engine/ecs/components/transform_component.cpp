#include "transform_component.hpp"

namespace chestnut
{
    STransformComponent::STransformComponent()
    {
        position = vec2f(0, 0);
        rotation = vec2f(1, 0);
        scale = vec2f(1, 1);
    }

    STransformComponent::STransformComponent(vec2f _position, vec2f _rotation, vec2f _scale)
    {
        position = _position;
        rotation = _rotation;
        scale = _scale;
    }

} // namespace chestnut
