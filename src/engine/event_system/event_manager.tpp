namespace chestnut
{ 
    template< typename EventType >
    listenerid_t CEventManager::registerListener( event_function( *func )( const EventType& ) ) 
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
    listenerid_t CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) ) 
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
    void CEventManager::unregisterListenerByID( listenerid_t id ) 
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
        std::vector< listenerid_t > &typedIDList = m_eventTypeToIDListMap[ TINDEX( EventType ) ];

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
    void CEventManager::constrainListenerByID( listenerid_t id, std::function< bool( const EventType& ) > constraintFunctor )
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

    template< typename EventType >
    EventType *CEventManager::raiseEvent() 
    {
        EventType *ptr = m_eventMemoryPool.create<EventType>();
        m_eventQueue.push( ptr );
        return ptr;
    }
    
} // namespace chestnut
