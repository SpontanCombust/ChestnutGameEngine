#include "event_manager.hpp"

namespace chestnut
{

    eventListener_id_t CEventManager::registerListener( SEventListener& listener ) 
    {
        // Creates new ID for the listener
        m_idCounter++;

        // Copies listener to ID-to-listener map under its designated ID
        m_IDToListenerMap[ m_idCounter ] = listener;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ listener.eventTindex ].push_back( m_idCounter );
        
        // Returns ID of the new listener
        return m_idCounter;
    }

    void CEventManager::unregisterListenerByID( eventListener_id_t id, std::type_index tindex ) 
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
        std::list< eventListener_id_t > &typedIDList = m_eventTypeToIDListMap[ tindex ];

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
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " and type " << tindex.name() << " exists!" );
        }
    }

    void CEventManager::raiseEvent( SEvent *event ) 
    {
        if( !event )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to raise null event!" );
            return;
        }

        m_eventQueue.push( event );
    }
    
    void CEventManager::clearListeners() 
    {
        // For every listener, free the memory from the invoker and constraint
        for( auto &pair : m_IDToListenerMap )
        {
            SEventListener listener = pair.second;

            destroyEventListener( listener );
        }

        // Clear maps from IDs and listener objects

        m_IDToListenerMap.clear();

        m_eventTypeToIDListMap.clear();
    }
    
    void CEventManager::clearEventQueue() 
    {
        while( !m_eventQueue.empty() )
        {
            SEvent *event = m_eventQueue.front();
            m_eventQueue.pop();
            
            delete event;
            event = nullptr;
        }
    }
    
    void CEventManager::delegateEvent( SEvent *event ) 
    {
        // Find the type of the event
        std::type_index tindex = TINDEX( *event );
        // Check if there are listeners with that type
        if( m_eventTypeToIDListMap.find( tindex ) != m_eventTypeToIDListMap.end() )
        {
            // Get list of listener IDs for that event type
            std::list< eventListener_id_t > &typedIDList = m_eventTypeToIDListMap[ tindex ];

            // Iterate over every ID in the list
            for( const eventListener_id_t &id : typedIDList )
            {
                // Get the specific listener
                SEventListener &listener = m_IDToListenerMap[ id ];

                if( listener.constraint )
                {
                    // If event doesn't fit constraint's demands, move onto next listener
                    if( !listener.constraint->verify( event ) )
                    {
                        continue;
                    }
                }
                
                listener.functionInvoker->invoke( event );
            }
        }
    }

    void CEventManager::delegateEvents() 
    {
        SEvent *event;
        while( !m_eventQueue.empty() )
        {
            event = m_eventQueue.front();
            m_eventQueue.pop();
            delegateEvent( event );
            
            delete event;
            event = nullptr;
        }
    }

    CEventManager::~CEventManager() 
    {
        clearEventQueue();
        clearListeners();        
    }

} // namespace chestnut
