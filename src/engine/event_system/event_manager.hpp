#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "event_listener.hpp"
#include "engine/debug/debug.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

#include <list>
#include <typeindex>
#include <unordered_map>
#include <queue>

namespace chestnut
{
    // Class processing raised events and triggering listeners registered for given events
    class CEventManager
    {
    private:
        listenerid_t m_idCounter = 0;

        std::unordered_map< std::type_index, std::list< listenerid_t > > m_eventTypeToIDListMap;
        std::unordered_map< listenerid_t, SEventListener > m_IDToListenerMap;
        std::queue< SEvent* > m_eventQueue;

    public:
        /* Registeres an event listener based on given event function
         * Returns id of the listener */
        template< typename EventType >
        listenerid_t registerListener( event_function ( *func )( const EventType& ) );

        /* Registeres an event listener based on given event member function
         * Returns id of the listener */
        template< typename T, typename EventType >
        listenerid_t registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) );

        // Registers the already ready SEventListener object
        listenerid_t registerListener( SEventListener& listener );

        // Removes the event listener with given ID
        template< typename EventType >
        void unregisterListenerByID( listenerid_t id );

        // Removes the event listener with given ID and type index
        void unregisterListenerByID( listenerid_t id, std::type_index tindex );

        // Sets a constraint for the event listener with given ID
        template< typename EventType >
        void constrainListenerByID( listenerid_t id, std::function< bool( const EventType& ) > constraintFunctor );

        // Puts the event in the event queue
        void raiseEvent( SEvent *event );

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