#include "event_manager.hpp"

namespace chestnut
{

    listenerid_t CEventManager::registerListener( IEventListener *listener ) 
    {
        if( listener )
        {
            // Creates new ID for the listener
            m_idCounter++;

            // Copies listener to ID-to-listener map under its designated ID
            m_IDToListenerMap[ m_idCounter ] = listener;

            // Adds new listener ID to type-to-IDs map
            m_eventTypeToIDListMap[ listener->eventTindex ].push_back( m_idCounter );
        }
        else
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Can't register a listener using null listener object!" );
            return LISTENER_ID_INVALID;
        }
        
        
        // Returns ID of the new listener
        return m_idCounter;
    }

    void CEventManager::unregisterListenerByID( listenerid_t id, eventtindex_t tindex ) 
    {
        // Checks if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " exists!" );
            return;
        }

        // Retrieves the listener from ID-to-listener map
        IEventListener *listener = m_IDToListenerMap[ id ];

        delete listener;

        // Erases listener from ID-to-listener map
        m_IDToListenerMap.erase( id );

        // Gets the refernce to the list of IDs of listeners for the event type
        std::vector< listenerid_t > &typedIDList = m_eventTypeToIDListMap[ tindex ];

        // Searches the list for the ID of unregistered listener and erases it
        auto it = std::find( typedIDList.begin(), typedIDList.end(), id );
        if( it != typedIDList.end() )
        {
            typedIDList.erase( it );
        }
    }

    void CEventManager::clearListeners() 
    {
        // For every listener, free the memory from the invoker and constraint
        for( auto &[ id, listener ] : m_IDToListenerMap )
        {
            delete listener;
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
            m_eventMemoryPool.remove( event );
        }
    }
    
    void CEventManager::delegateEvent( SEvent *event ) 
    {
        // Find the type of the event
        eventtindex_t tindex = TINDEX( *event );
        // Check if there are listeners with that type
        if( m_eventTypeToIDListMap.find( tindex ) != m_eventTypeToIDListMap.end() )
        {
            // Get list of listener IDs for that event type
            std::vector< listenerid_t > &typedIDList = m_eventTypeToIDListMap[ tindex ];

            // Iterate over every ID in the list
            for( const listenerid_t &id : typedIDList )
            {
                // Get the specific listener
                IEventListener *listener = m_IDToListenerMap[ id ];

                // First check if event fits constraint's demands
                if( listener->checkConstraint( event ) )
                {
                    listener->invoke( event );
                }
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
            m_eventMemoryPool.remove( event );
        }
    }

    CEventManager::~CEventManager() 
    {
        clearEventQueue();
        clearListeners();        
    }

} // namespace chestnut
