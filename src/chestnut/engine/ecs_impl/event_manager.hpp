#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/types.hpp"
#include "chestnut/engine/constants.hpp"
#include "chestnut/engine/ecs_impl/event_listener.hpp"

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


#include "event_manager.inl"


