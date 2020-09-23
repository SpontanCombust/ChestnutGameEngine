#include "engine/ecs/components/transform_component.hpp"

namespace chestnut
{
    STransformComponent::STransformComponent()
    : position( {0, 0} ), rotation( {0, 1} ), scale( {1, 1} )
    {

    }

    const std::string STransformComponent::getTypeStatic()
    {
        return "transform";
    }

} // namespace chestnut
