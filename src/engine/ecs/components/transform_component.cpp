#include "engine/ecs/components/transform_component.hpp"

namespace chestnut
{
    STransformComponent::STransformComponent()
    : position( {0, 0} ), rotation( {0, 1} ), scale( {1, 1} )
    {

    }

    STransformComponent::STransformComponent(Vector2f _position, Vector2f _rotation, Vector2f _scale)
    : position( _position ), rotation( _rotation ), scale( _scale )
    {

    }

    const std::string STransformComponent::getTypeStringStatic()
    {
        return "transform";
    }

} // namespace chestnut
