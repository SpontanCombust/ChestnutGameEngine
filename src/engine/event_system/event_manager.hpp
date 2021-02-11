#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "function_invoker.hpp"
#include "event_constraint.hpp"
#include "engine/debug/debug.hpp"
#include "engine/misc/utils.hpp"

#include <list>
#include <typeindex>
#include <unordered_map>
#include <queue>

namespace chestnut
{
    // Struct containing function invoker and its (optional) constraint
    struct SEventListener 
    { 
        IFunctionInvoker *functionInvoker;
        IEventConstraint *constraint;
    };

    using eventListener_id_t = unsigned int;

    // Class processing raised events and triggering listeners registered for given events
    class CEventManager
    {
    private:
        eventListener_id_t m_idCounter = 0;

        std::unordered_map< std::type_index, std::list< eventListener_id_t > > m_eventTypeToIDListMap;
        std::unordered_map< eventListener_id_t, SEventListener > m_IDToListenerMap;
        std::queue< SEvent* > m_eventQueue;

    public:
        /* Registeres an event listener based on given event function
         * Returns id of the listener */
        template< typename EventType >
        eventListener_id_t registerListener( event_function ( *func )( const EventType& ) );

        /* Registeres an event listener based on given event member function
         * Returns id of the listener */
        template< typename T, typename EventType >
        eventListener_id_t registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) );

        // Removes the event listener with given ID
        template< typename EventType >
        void unregisterListenerByID( eventListener_id_t ID );

        // Sets a constraint for the event listener with given ID
        template< typename EventType >
        void constrainListenerByID( eventListener_id_t id, std::function< bool( const EventType& ) > constraintFunctor );

        // Puts the event in the event queue
        void raiseEvent( SEvent *event );

        // Removes all event listeners
        void clearListeners();

        // Processes all events in the event queue
        void update( float deltaTime );

        ~CEventManager();

    private:
        // empties the event queue and frees the memory from remaining event
        void clearEventQueue();
        // invokes listeners' functions using given event
        void delegateEvent( SEvent *event );
        // invokes listeners' events using events in the queue
        void delegateEvents();
    };

    template< typename EventType >
    eventListener_id_t CEventManager::registerListener( event_function( *func )( const EventType& ) ) 
    {
        if( !func )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null function ptr!" );
            return 0;
        }

        // Creates new ID for the listener
        m_idCounter++;

        // Initializes the new listener in ID-to-listener map
        SEventListener &listener = m_IDToListenerMap[ m_idCounter ];

        // Creates function invoker based on function in the parameter
        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();
        invoker->bind( func );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ TINDEX( EventType ) ].push_back( m_idCounter );
        
        // Returns ID of the new listener
        return m_idCounter;
    }
    

    template< typename T, typename EventType >
    eventListener_id_t CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) ) 
    {
        if( !objPtr || !membFunc )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null object or member function ptr!" );
            return 0;
        }

        // Creates new ID for the listener
        m_idCounter++;

        // Initializes the new listener in ID-to-listener map
        SEventListener &listener = m_IDToListenerMap[ m_idCounter ];
        
        // Creates member function invoker based on function in the parameter
        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();
        invoker->bind( objPtr, membFunc );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ TINDEX( EventType ) ].push_back( m_idCounter );

        // Returns ID of the new listener
        return m_idCounter;
    }
    

    template< typename EventType >
    void CEventManager::unregisterListenerByID( eventListener_id_t id ) 
    {
        // Checks if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " exists!" );
            return;
        }

        // Retrieves the listener from ID-to-listener map
        SEventListener &listener = m_IDToListenerMap[ id ];

        // Deletes listener's invoker
        delete listener.functionInvoker;

        // If the listener also had a constraint, deletes it as well
        if( listener.constraint )
            delete listener.constraint;

        // Erases listener from ID-to-listener map
        m_IDToListenerMap.erase( id );

        // Gets the refernce to the list of IDs of listeners for the event type
        std::list< eventListener_id_t > &typedIDList = m_eventTypeToIDListMap[ TINDEX( EventType ) ];

        // Searches the list for the ID of unregistered listener and erases it
        for( auto it = typedIDList.begin(); it != typedIDList.end(); ++it )
        {
            if( *it == id )
            {
                typedIDList.erase( it );
                break;
            }
        }
    }


    template< typename EventType >
    void CEventManager::constrainListenerByID( eventListener_id_t id, std::function< bool( const EventType& ) > constraintFunctor )
    {
        // Checks if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " exists!" );
            return;
        }
        
        // Retrieves the listener from ID-to-listener map
        SEventListener &listener = m_IDToListenerMap[ id ];

        // Checks if the given constraint is for the same event type as the function invoker
        if( TINDEX( listener.functionInvoker ) != TINDEX( EventType ) )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Event constraint incompatable with the listener!" );
            return;
        }

        // If constraint hasn't been set earlier, make a new one
        if( !listener.constraint )
        {
            listener.constraint = new CEventConstraint<EventType>();
        }

        // Retrieve the constraint
        CEventConstraint<EventType> *constraint = listener.constraint;

        // Set the functor for the constraint
        constraint->set( constraintFunctor );
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_MANAGER_H__