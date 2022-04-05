#include "event_manager.hpp"

#include "../debug/log.hpp"

namespace chestnut::engine
{        
    void CEventManager::registerListener( IEventListener *listener, listenerpriority_t priority ) 
    {
        if( !listener )
        {
            LOG_WARNING( "Attempt was made to register a null listener!" );
            return;
        }

        std::type_index eventType = listener->m_eventType;

        auto& listNodes = m_mapEventTypeToListListenerNodes[ eventType ];

        // looking for a spot to place listener in according to the priority
        auto it = listNodes.begin();
        for( ;it != listNodes.end(); ++it)
        {
            if( it->priority >= priority )
            {
                break;
            }
        }

        SEventListenerNode node { listener, priority };

        listNodes.insert( it, node );
    }

    void CEventManager::unregisterListener( IEventListener *listener ) 
    {
        if( listener )
        {
            std::type_index eventType = listener->m_eventType;

            auto& listNodes = m_mapEventTypeToListListenerNodes[ eventType ];

            for( auto it = listNodes.begin(); it != listNodes.end(); ++it )
            {
                // compare if it's the same pointer
                if( it->listener == listener )
                {
                    listNodes.erase( it );
                    break;
                }
            }
        }
    }


} // namespace chestnut::engine
