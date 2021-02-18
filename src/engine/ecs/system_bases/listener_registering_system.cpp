#include "listener_registering_system.hpp"

namespace chestnut
{    
    bool CListenerRegisteringSystem::needsToManageListeners() 
    {
        return !m_listenersToBeRegistered.empty() || !m_listenersToBeUnregisteredDataPairs.empty();
    }

    void CListenerRegisteringSystem::manageListeners( CEventManager& eventManagerRef ) 
    {
        for( SEventListener& listener : m_listenersToBeRegistered )
        {
            eventManagerRef.registerListener( listener );
        }

        m_listenersToBeRegistered.clear();

        for( auto& pair : m_listenersToBeUnregisteredDataPairs )
        {
            eventListener_id_t lid = pair.first;
            std::type_index tindex = pair.second;
            eventManagerRef.unregisterListenerByID( lid, tindex );
        }

        m_listenersToBeUnregisteredDataPairs.clear();
    }

} // namespace chestnut
