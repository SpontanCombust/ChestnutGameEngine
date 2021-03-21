namespace chestnut
{
    template< typename EventType >
    SEventListener createEventListener( event_function ( *func )( const EventType& ) )
    {
        SEventListener listener;

        // assign type index to maintain coherence when setting constraint
        listener.eventTindex = TINDEX( EventType );

        // Creates function invoker based on function in the parameter
        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();
        invoker->bind( func );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        return listener;
    }

    template< typename T, typename EventType >
    SEventListener createEventListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) )
    {
        if( !objPtr )
        {
            throw ChestnutException( "Can't create an event listener for a null object!" );
        }

        SEventListener listener;

        // assign type index to maintain coherence when setting constraint
        listener.eventTindex = TINDEX( EventType );

        // Creates member function invoker based on function in the parameter
        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();
        invoker->bind( objPtr, membFunc );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        return listener;  
    }

    template< typename EventType >
    void constrainEventListener( SEventListener& listener, std::function< bool( const EventType& ) > constraintFunctor )
    {
        // Checks if the given constraint functor is for the same event type as the function invoker
        if( !listener.functionInvoker || listener.eventTindex != TINDEX( EventType ) )
        {
            throw ChestnutException( "Can't constrain event listener with incompatible constraint functor!" );
        }

        // Retrieve the constraint
        CEventConstraint<EventType> *constraint;

        // If constraint has been set earlier, retrieve it
        if( listener.constraint )
        {
            constraint = dynamic_cast< CEventConstraint<EventType>* >( listener.constraint );
        }
        // ...if not, create a new one
        else
        {
            constraint = new CEventConstraint<EventType>();
        }

        // Set the functor for the constraint
        constraint->set( constraintFunctor );

        // assign new constraint
        listener.constraint = constraint;
    }

} // namespace chestnut
