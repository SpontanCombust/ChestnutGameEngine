#pragma once

#include "../../physics/collider2d.hpp"

#include <chestnut/ecs/types.hpp>

namespace chestnut::engine
{
    struct SCollisionEvent
    {
        ecs::entityid_t entity1;
        ecs::entityid_t entity2;
        SCollisionResolutionData resolutionData;
    };

} // namespace chestnut::engine
