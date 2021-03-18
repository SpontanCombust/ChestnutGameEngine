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

        // Registers the already ready SEventListener object
        eventListener_id_t registerListener( SEventListener& listener );

        // Removes the event listener with given ID
        template< typename EventType >
        void unregisterListenerByID( eventListener_id_t id );

        // Removes the event listener with given ID and type index
        void unregisterListenerByID( eventListener_id_t id, std::type_index tindex );

        // Sets a constraint for the event listener with given ID
        template< typename EventType >
        void constrainListenerByID( eventListener_id_t id, std::function< bool( const EventType& ) > constraintFunctor );

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

    template< typename EventType >
    eventListener_id_t CEventManager::registerListener( event_function( *func )( const EventType& ) ) 
    {
        SEventListener listener = createEventListener( func );

        // Creates new ID for the listener
        m_idCounter++;

        // Copies listener to ID-to-listener map under its designated ID
        m_IDToListenerMap[ m_idCounter ] = listener;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ listener.eventTindex ].push_back( m_idCounter );
        
        // Returns ID of the new listener
        return m_idCounter;
    }
    

    template< typename T, typename EventType >
    eventListener_id_t CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) ) 
    {
        SEventListener listener;

        try
        {
            listener = createEventListener( objPtr, membFunc );
        }
        catch(const std::exception& e)
        {
            LOG_CHANNEL( "EVENT_MANAGER", e.what() );
            return 0;
        }
        
        // Creates new ID for the listener
        m_idCounter++;

        // Copies listener to ID-to-listener map under its designated ID
        m_IDToListenerMap[ m_idCounter ] = listener;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ listener.eventTindex ].push_back( m_idCounter );
        
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

        destroyEventListener( listener );

        // Erases listener from ID-to-listener map
        m_IDToListenerMap.erase( id );

        // Gets the refernce to the list of IDs of listeners for the event type
        std::list< eventListener_id_t > &typedIDList = m_eventTypeToIDListMap[ TINDEX( EventType ) ];

        // Searches the list for the ID of unregistered listener and erases it
        bool found = false;
        for( auto it = typedIDList.begin(); it != typedIDList.end(); ++it )
        {
            if( *it == id )
            {
                typedIDList.erase( it );
                found = true;
                break;
            }
        }

        if( !found )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " and type " << TINDEX_NAME( EventType ) << " exists!" );
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

        try
        {
            constrainEventListener( listener, constraintFunctor );
        }
        catch(const std::exception& e)
        {
            LOG_CHANNEL( "EVENT_MANAGER", e.what() );
            return;
        }
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_MANAGER_H__