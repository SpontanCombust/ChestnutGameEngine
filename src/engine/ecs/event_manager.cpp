#include "event_manager.hpp"

namespace chestnut
{        
    void CEventManager::registerListener( std::weak_ptr<IEventListener> listener ) 
    {
        if( auto shared = listener.lock() )
        {
            std::type_index eventType = shared->m_eventType;

            m_mapEventTypeToVecListeners[ eventType ].push_back( listener );
        }
    }

    void CEventManager::unregisterListener( std::weak_ptr<IEventListener> listener ) 
    {
        if( auto shared = listener.lock() )
        {
            std::type_index eventType = shared->m_eventType;

            auto& vecListeners = m_mapEventTypeToVecListeners[ eventType ];

            for( auto it = vecListeners.begin(); it != vecListeners.end(); ++it )
            {
                auto testShared = it->lock();

                // comparing raw pointer values stored in listener smart pointers
                if( testShared && testShared == shared )
                {
                    vecListeners.erase( it );
                    break;
                }
            }
        }
    }


} // namespace chestnut
