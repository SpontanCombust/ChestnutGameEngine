#ifndef __CHESTNUT_ENGINE_EVENT_MANAGER_H__
#define __CHESTNUT_ENGINE_EVENT_MANAGER_H__

#include "../types.hpp"
#include "../constants.hpp"
#include "event_listener.hpp"

#include <list>
#include <memory> // weak_ptr
#include <typeindex>
#include <unordered_map>

namespace chestnut
{
    class CEventManager
    {
    private:
        struct SEventListenerNode
        {
            std::weak_ptr<IEventListener> weakPtr;
            listenerpriority_t priority;
        };

        std::unordered_map< std::type_index, std::list< SEventListenerNode > > m_mapEventTypeToListListenerNodes;

    public:
        ~CEventManager() = default;


        void registerListener( std::weak_ptr<IEventListener> listener, listenerpriority_t priority = LISTENER_PRIORITY_ANY );

        void unregisterListener( std::weak_ptr<IEventListener> listener );

        template< typename EventType >
        void raiseEvent( const EventType& event );
    };

} // namespace chestnut


#include "event_manager.tpp"


#endif // __CHESTNUT_ENGINE_EVENT_MANAGER_H__