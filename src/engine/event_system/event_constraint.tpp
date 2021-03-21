namespace chestnut
{
    template< typename EventType >
    void CEventConstraint<EventType>::set( std::function< bool( const EventType& ) > eventConstraintFunctor ) 
    {
        m_wasSet = true;
        m_eventConstraintFunctor = eventConstraintFunctor;
    }

    template< typename EventType >
    bool CEventConstraint<EventType>::verify( SEvent *event )
    {
        if( !m_wasSet )
        {
            return true;
        }

        return m_eventConstraintFunctor( *dynamic_cast<EventType*>( event ) );
    }
    
} // namespace chestnut
