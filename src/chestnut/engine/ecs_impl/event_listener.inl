namespace chestnut::engine
{
    template<typename EventType>
    CEventListener<EventType>::CEventListener() 
    {
        m_eventType = typeid(EventType);

        m_handler = []( const EventType& ) -> event_function
        {
            //NOP
        };

        m_filter = []( const EventType& ) -> bool
        {
            // by default filter accepts anything
            return true;
        };
    }

    template<typename EventType>
    CEventListener<EventType>::CEventListener( std::function< event_function( const EventType& ) > handler ) 
    {
        m_eventType = typeid(EventType);

        m_handler = handler;
        m_filter = []( const EventType& ) -> bool
        {
            // by default filter accepts anything
            return true;
        };
    }

    template<typename EventType>
    CEventListener<EventType>::CEventListener( std::function< event_function( const EventType& ) > handler, std::function< bool( const EventType& ) > filter ) 
    {
        m_eventType = typeid(EventType);

        m_handler = handler;
        m_filter = filter;
    }

    template<typename EventType>
    void CEventListener<EventType>::setHandler( std::function< event_function( const EventType& ) > handler ) 
    {
        m_handler = handler;
    }

    template<typename EventType>
    template<typename T>
    void CEventListener<EventType>::setHandler( event_function ( T::*handler )( const EventType& ), T *obj ) 
    {
        m_handler = std::bind( handler, obj, std::placeholders::_1 );
    }

    template<typename EventType>
    void CEventListener<EventType>::setFilter( std::function< bool ( const EventType& ) > filter ) 
    {
        m_filter = filter;
    }

    template<typename EventType>
    void CEventListener<EventType>::invokeHandler( const EventType& event ) 
    {
        m_handler( event );
    }

    template<typename EventType>
    bool CEventListener<EventType>::testFilter( const EventType& event ) 
    {
        return m_filter( event );
    }

    template<typename EventType>
    void CEventListener<EventType>::invokeHandlerIfFilterAccepts( const EventType& event ) 
    {
        if( m_filter( event ) )
        {
            m_handler( event );
        }
    }

} // namespace chestnut::engine
