#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CTimerSystem : public ILogicSystem
    {
    private:
        ecs::CEntityQuery *m_timerQuery;

    public:
        CTimerSystem() = default;
        CTimerSystem(systempriority_t priority);
        ~CTimerSystem();

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

