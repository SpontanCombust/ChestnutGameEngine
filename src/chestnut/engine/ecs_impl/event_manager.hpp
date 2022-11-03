#ifndef __CHESTNUT_ENGINE_EVENT_MANAGER_H__
#define __CHESTNUT_ENGINE_EVENT_MANAGER_H__

#include "chestnut/engine/macros.hpp"
#include "../types.hpp"
#include "../constants.hpp"
#include "event_listener.hpp"

#include <list>
#include <typeindex>
#include <unordered_map>

namespace chestnut::engine
{
    class CHESTNUT_API CEventManager
    {
    private:
        struct SEventListenerNode
        {
            IEventListener *listener;
            listenerpriority_t priority;
        };

        std::unordered_map< std::type_index, std::list< SEventListenerNode > > m_mapEventTypeToListListenerNodes;

    public:
        ~CEventManager() = default;


        void registerListener( IEventListener *listener, listenerpriority_t priority = LISTENER_PRIORITY_ANY );

        void unregisterListener( IEventListener *listener );

        template< typename EventType >
        void raiseEvent( const EventType& event );
    };

} // namespace chestnut::engine


#include "event_manager.tpp"


#endif // __CHESTNUT_ENGINE_EVENT_MANAGER_H__