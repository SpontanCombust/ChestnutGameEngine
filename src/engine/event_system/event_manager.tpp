namespace chestnut
{ 
    template< typename EventType >
    listenerid_t CEventManager::registerListener( event_function( *func )( const EventType& ) ) 
    {
        CEventListener<EventType> *listener = createEventListener( std::bind( func, std::placeholders::_1 ) );

        // Creates new ID for the listener
        m_idCounter++;

        // Copies listener to ID-to-listener map under its designated ID
        m_IDToListenerMap[ m_idCounter ] = listener;

        // Adds new listener ID to type-to-IDs map
        m_eventTypeToIDListMap[ listener->eventTindex ].push_back( m_idCounter );
        
        // Returns ID of the new listener
        return m_idCounter;
    }
    

    template< typename T, typename EventType >
    listenerid_t CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) ) 
    {
        if( objPtr )
        {
            CEventListener<EventType> *listener = nullptr;

            listener = createEventListener<EventType>( std::bind( membFunc, objPtr, std::placeholders::_1 ) );
                    
            // Creates new ID for the listener
            m_idCounter++;

            // Copies listener to ID-to-listener map under its designated ID
            m_IDToListenerMap[ m_idCounter ] = listener;

            // Adds new listener ID to type-to-IDs map
            m_eventTypeToIDListMap[ listener->eventTindex ].push_back( m_idCounter );
            
            // Returns ID of the new listener
            return m_idCounter;
        }
        else
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Can't register a listener for null object!" );
            return LISTENER_ID_INVALID;
        }
    }
    

    template< typename EventType >
    void CEventManager::unregisterListenerByID( listenerid_t id ) 
    {
        unregisterListenerByID( id, TINDEX(EventType) );
    }


    template< typename EventType >
    listenerid_t CEventManager::constrainListenerByID( listenerid_t id, std::function< bool( const EventType& ) > constraintFunctor )
    {
        // Checks if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "No listener with ID " << id << " exists!" );
            return LISTENER_ID_INVALID;
        }
        
        // Retrieves the listener from ID-to-listener map
        IEventListener *untypedListener = m_IDToListenerMap[ id ];
        CEventListener<EventType> *typedListener = dynamic_cast< CEventListener<EventType> * >( untypedListener );

        try
        {
            constrainEventListener( typedListener, constraintFunctor );
        }
        catch(const std::exception& e)
        {
            LOG_CHANNEL( "EVENT_MANAGER", e.what() );
            return LISTENER_ID_INVALID;
        }

        return id;
    }

    template< typename EventType >
    EventType *CEventManager::raiseEvent() 
    {
        EventType *ptr = m_eventMemoryPool.create<EventType>();
        m_eventQueue.push( ptr );
        return ptr;
    }
    
} // namespace chestnut
