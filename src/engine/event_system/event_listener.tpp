namespace chestnut
{
    template< typename EventType >
    CEventListener<EventType>::CEventListener() 
    {
        func =
        []( const EventType& )
        {
            // NOP
        };

        constraint =
        []( const EventType& )
        {
            // listener at first doesn't filter out events
            return true;
        };
    }

    template< typename EventType >
    CEventListener<EventType> *createEventListener( std::function< event_function ( const EventType& ) > func )
    {
        CEventListener<EventType> *listener = new CEventListener<EventType>();

        // assign type index to maintain coherence when setting constraint
        listener->eventTindex = TINDEX( EventType );

        listener->func = func;

        return listener;
    }

    template< typename EventType >
    void constrainEventListener( CEventListener<EventType> *listener, std::function< bool( const EventType& ) > constraintFunctor )
    {
        if( listener )
        {
            if( listener->eventTindex != TINDEX( EventType ) )
            {
                throw ChestnutException( "Can't constrain event listener with incompatible constraint functor!" );
            }

            listener->constraint = constraintFunctor;
        }
    }

    template<typename EventType>
    void CEventListener<EventType>::invoke( SEvent *event ) 
    {
        func( *dynamic_cast< EventType * >( event ) );
    }

    template<typename EventType>
    bool CEventListener<EventType>::checkConstraint( SEvent *event ) 
    {
        return constraint( *dynamic_cast< EventType * >( event ) );
    }

} // namespace chestnut
