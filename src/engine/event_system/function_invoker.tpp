namespace chestnut
{
    template< typename EventType >
    void CFunctionInvoker<EventType>::bind( event_function( *func )( const EventType& ) ) 
    {
        m_wasBound = true;
        m_func = func;
    }
    
    template< typename EventType >
    void CFunctionInvoker<EventType>::invoke( SEvent *event ) 
    {
        if( m_wasBound )
        {
            ( *m_func )( *dynamic_cast< EventType* >( event ) );
        }
    }


    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::bind( T *objPtr, event_function ( T::*membFunc )( const EventType& ) )
    {
        m_wasBound = true;
        m_objPtr = objPtr;
        m_membFunc = membFunc;
    }

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::invoke( SEvent* event )
    {
        if( m_wasBound )
        {
            ( m_objPtr->*m_membFunc )( *dynamic_cast< EventType* >( event ) );
        }
    }

} // namespace chestnut
