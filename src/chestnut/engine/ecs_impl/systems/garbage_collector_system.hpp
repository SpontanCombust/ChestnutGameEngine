#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"
#include "chestnut/engine/misc/locked_manual_timer.hpp"

namespace chestnut::engine
{
    class CGarbageCollectorSystem : public ILogicSystem
    {
    private:
        CLockedManualTimer m_timer;

    public:
        CGarbageCollectorSystem() = default;
        CGarbageCollectorSystem(systempriority_t prio);

        void update(float dt) override;
    };

} // namespace chestnut::engine
