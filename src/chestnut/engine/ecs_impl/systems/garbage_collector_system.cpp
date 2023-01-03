#include "chestnut/engine/ecs_impl/systems/garbage_collector_system.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
{
    CGarbageCollectorSystem::CGarbageCollectorSystem(systempriority_t prio)
    : ILogicSystem(prio),
      m_timer(0, 2.f, true)
    {
        m_timer.start();
    }

    void CGarbageCollectorSystem::update(float dt) 
    {
        if(m_timer.tick(dt))
        {
            int n = CEngine::getInstance()
            .getResourceManager()
            .freeUnusedResources();

            if(n > 0)
            {
                LOG_INFO("Freed " << n << " resources");
            }
        }
    }

} // namespace chestnut::engine
