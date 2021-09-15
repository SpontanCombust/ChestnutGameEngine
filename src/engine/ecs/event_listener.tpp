namespace chestnut
{
    template<typename EventType>
    CEventListener<EventType>::CEventListener() 
    {
        m_eventType = typeid(EventType);

        m_isEnabled = true;

        m_consumer = []( const EventType& ) -> event_function
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
    CEventListener<EventType>::CEventListener( std::function< event_function( const EventType& ) > consumer ) 
    {
        m_eventType = typeid(EventType);

        m_isEnabled = true;

        m_consumer = consumer;

        m_filter = []( const EventType& ) -> bool
        {
            // by default filter accepts anything
            return true;
        };
    }

    template<typename EventType>
    CEventListener<EventType>::CEventListener( std::function< event_function( const EventType& ) > consumer, std::function< bool( const EventType& ) > filter ) 
    {
        m_eventType = typeid(EventType);

        m_isEnabled = true;
        
        m_consumer = consumer;

        m_filter = filter;
    }

    template<typename EventType>
    void CEventListener<EventType>::setConsumer( std::function< event_function( const EventType& ) > consumer ) 
    {
        m_consumer = consumer;
    }

    // template<typename EventType>
    // void CEventListener<EventType>::setConsumer( event_function( *consumer )( const EventType& ) ) 
    // {
    //     m_consumer = std::bind( consumer, std::placeholders::_1 );
    // }

    template<typename EventType>
    template<typename T>
    void CEventListener<EventType>::setConsumer( event_function ( T::*consumer )( const EventType& ), T *obj ) 
    {
        m_consumer = std::bind( consumer, obj, std::placeholders::_1 );
    }

    template<typename EventType>
    void CEventListener<EventType>::setFilter( std::function< bool ( const EventType& ) > filter ) 
    {
        m_filter = filter;
    }

    template<typename EventType>
    void CEventListener<EventType>::invokeConsumer( const EventType& event ) 
    {
        m_consumer( event );
    }

    template<typename EventType>
    bool CEventListener<EventType>::testFilter( const EventType& event ) 
    {
        return m_filter( event );
    }

    template<typename EventType>
    void CEventListener<EventType>::invokeConsumerIfFilterAccepts( const EventType& event ) 
    {
        if( m_filter( event ) )
        {
            m_consumer( event );
        }
    }

} // namespace chestnut
