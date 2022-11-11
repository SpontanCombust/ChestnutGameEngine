#include "chestnut/engine/ecs_impl/system.hpp"
#include "chestnut/engine/constants.hpp"

namespace chestnut::engine
{
    ISystem::ISystem()
    : m_priority(SYSTEM_PRIORITY_ANY)
    {

    }

    ISystem::ISystem(systempriority_t priority)
    : m_priority(priority)
    {

    }

    void ISystem::setPriority(systempriority_t priority)
    {
        m_priority = priority;
    }

    systempriority_t ISystem::getPriority() const
    {
        return m_priority;
    }

} // namespace chestnut::engine
