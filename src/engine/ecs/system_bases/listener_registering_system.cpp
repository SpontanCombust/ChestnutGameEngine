#include "listener_registering_system.hpp"

namespace chestnut
{    
    bool CListenerRegisteringSystem::needsToRegisterListeners() 
    {
        return !m_listenersToBeRegistered.empty();
    }

    void CListenerRegisteringSystem::registerListeners( CEventManager& eventManagerRef ) 
    {
        for( SEventListener listener : m_listenersToBeRegistered )
        {
            eventManagerRef.registerListener( listener );
        }

        m_listenersToBeRegistered.clear();
    }

} // namespace chestnut
