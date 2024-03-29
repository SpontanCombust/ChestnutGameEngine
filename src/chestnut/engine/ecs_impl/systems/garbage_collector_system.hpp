#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"
#include "chestnut/engine/misc/locked_manual_timer.hpp"

namespace chestnut::engine
{
    class CHESTNUT_API CGarbageCollectorSystem : public ILogicSystem
    {
    private:
        CLockedManualTimer m_timer;

    public:
        CGarbageCollectorSystem();
        CGarbageCollectorSystem(systempriority_t prio);

        void onAttach() override;
        void onDetach() override;

        void update(float dt) override;
    };

} // namespace chestnut::engine
