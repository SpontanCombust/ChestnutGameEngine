#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "event_listener.hpp"
#include "../debug/debug.hpp"
#include "../misc/tindex.hpp"
#include "../types.hpp"
#include "../constants.hpp"
#include "../memory/multi_type_dynamic_memory_pool.hpp"

#include <unordered_map>
#include <vector>
#include <queue>

namespace chestnut
{
    // Class processing raised events and triggering listeners registered for given events
    class CEventManager
    {
    private:
        listenerid_t m_idCounter = 0;

        std::unordered_map< eventtindex_t, std::vector< listenerid_t > > m_eventTypeToIDListMap;
        std::unordered_map< listenerid_t, IEventListener* > m_IDToListenerMap;

        CMultiTypeDynamicMemoryPool m_eventMemoryPool;
        std::queue< SEvent* > m_eventQueue;

    public:
        // Registeres an event listener based on given event function
        // Returns id of the listener
        template< typename EventType >
        listenerid_t registerListener( event_function ( *func )( const EventType& ) );

        // Registeres an event listener based on given event member function
        // Returns id of the listener on success, LISTENER_ID_INVALID on failure
        template< typename T, typename EventType >
        listenerid_t registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) );

        // Registers an event listener with already existing listener object
        // Returns id of the listener on success, LISTENER_ID_INVALID on failure
        listenerid_t registerListener( IEventListener *listener );

        // Removes the event listener with given ID
        template< typename EventType >
        void unregisterListenerByID( listenerid_t id );

        // Removes the event listener with given ID and type index
        void unregisterListenerByID( listenerid_t id, eventtindex_t tindex );

        // Sets a constraint for the event listener with given ID
        // Returns passed listener id on success, LISTENER_ID_INVALID on failure
        template< typename EventType >
        listenerid_t constrainListenerByID( listenerid_t id, std::function< bool( const EventType& ) > constraintFunctor );

        // Creates event and returns a pointer to it, event manager maintains the ownership
        template< typename EventType >
        EventType *raiseEvent();

        // Removes all event listeners
        void clearListeners();

        // invokes listeners' functions using events in the queue
        void delegateEvents();

        ~CEventManager();

    private:
        // empties the event queue and frees the memory from remaining event
        void clearEventQueue();
        // invokes listeners' functions using given event
        void delegateEvent( SEvent *event );
    };

} // namespace chestnut


#include "event_manager.tpp"


#endif // __CHESTNUT_EVENT_MANAGER_H__