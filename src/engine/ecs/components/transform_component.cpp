#include "transform_component.hpp"

namespace chestnut
{
    STransformComponent::STransformComponent()
    {
        position = vec2f(0, 0);
        scale = vec2f(1, 1);
        rotation = 0.0;
    }

    STransformComponent::STransformComponent(vec2f _position, vec2f _scale, double _rotation )
    {
        position = _position;
        scale = _scale;
        rotation = _rotation;
    }

} // namespace chestnut
