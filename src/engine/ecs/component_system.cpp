#include "engine/ecs/component_system.hpp"

namespace chestnut
{
    void IComponentSystem::setPriority( unsigned int priority ) 
    {
        m_priority = priority;
    }

    unsigned int IComponentSystem::getPriority() 
    {
        return m_priority;
    }
    
} // namespace chestnut
