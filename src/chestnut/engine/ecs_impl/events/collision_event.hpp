#ifndef __CHESTNUT_ENGINE_COLLISION_EVENT_H__
#define __CHESTNUT_ENGINE_COLLISION_EVENT_H__

#include "../../physics/collider.hpp"

#include <chestnut/ecs/types.hpp>


namespace chestnut::engine
{
    struct SCollisionEvent
    {
        ecs::entityid entity1;
        ecs::entityid entity2;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION_EVENT_H__