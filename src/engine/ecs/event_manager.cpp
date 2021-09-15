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

} // namespace chestnut
