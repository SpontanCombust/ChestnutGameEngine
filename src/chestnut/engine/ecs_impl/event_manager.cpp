#include "event_manager.hpp"

namespace chestnut
{        
    void CEventManager::registerListener( std::weak_ptr<IEventListener> listener, listenerpriority_t priority ) 
    {
        if( auto shared = listener.lock() )
        {
            std::type_index eventType = shared->m_eventType;

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
    }

    void CEventManager::unregisterListener( std::weak_ptr<IEventListener> listener ) 
    {
        if( auto shared = listener.lock() )
        {
            std::type_index eventType = shared->m_eventType;

            auto& listNodes = m_mapEventTypeToListListenerNodes[ eventType ];

            for( auto it = listNodes.begin(); it != listNodes.end(); ++it )
            {
                auto itShared = it->weakPtr.lock();

                // comparing raw pointer values stored in listener smart pointers
                if( itShared && itShared == shared )
                {
                    listNodes.erase( it );
                    break;
                }
            }
        }
    }


} // namespace chestnut
