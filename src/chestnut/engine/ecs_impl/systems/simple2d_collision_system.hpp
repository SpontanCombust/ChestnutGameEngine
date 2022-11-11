#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CSimple2DCollisionSystem : public ILogicSystem
    {
    private:
        ecs::CEntityQuery *m_collisionQuery;

    public:
        CSimple2DCollisionSystem() = default;
        CSimple2DCollisionSystem(systempriority_t priority);
        ~CSimple2DCollisionSystem();

        void update( float dt ) override;
    };

} // namespace chestnut::engine

