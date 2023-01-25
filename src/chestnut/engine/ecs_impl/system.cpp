#include "chestnut/engine/ecs_impl/system.hpp"
#include "chestnut/engine/constants.hpp"
#include "chestnut/engine/main/engine.hpp"

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

    ISystem::~ISystem() 
    {
        for(auto& [_, listener] : m_mapEventListeners)
        {
            CEngine::getInstance().getEventManager().unregisterListener(listener);
        }
    }

    void ISystem::setPriority(systempriority_t priority)
    {
        m_priority = priority;
    }

    systempriority_t ISystem::getPriority() const
    {
        return m_priority;
    }

    void ISystem::addEventListener(const char *name, IEventListener *listener) 
    {
        removeEventListener(name);
        CEngine::getInstance().getEventManager().registerListener(listener);
        m_mapEventListeners[name] = listener;
    }

    void ISystem::addEventListener(const char *name, IEventListener *listener, listenerpriority_t priority) 
    {
        removeEventListener(name);
        CEngine::getInstance().getEventManager().registerListener(listener, priority);
        m_mapEventListeners[name] = listener;
    }

    void ISystem::removeEventListener(const char *name) 
    {
        auto it = m_mapEventListeners.find(name);
        if(it != m_mapEventListeners.end())
        {
            CEngine::getInstance().getEventManager().unregisterListener(it->second);
            m_mapEventListeners.erase(it);
        }
    }

} // namespace chestnut::engine
