namespace chestnut::engine
{    
    template<typename EventType>
    void CEventManager::raiseEvent( const EventType& event ) 
    {
        std::type_index type = typeid(EventType);

        auto& listNodes = m_mapEventTypeToListListenerNodes[ type ];

        if( !listNodes.empty() )
        {
            // iterate using iterator type so we can erase a listener if its pointer is exprired
            for( const auto& node : listNodes )
            {
                if( node.listener->isEnabled() )
                {
                    // we can use static cast as we store the type data in the listener itself
                    CEventListener<EventType> *listenerCasted = static_cast< CEventListener<EventType> * >( node.listener );

                    listenerCasted->invokeHandlerIfFilterAccepts( event );
                }
            }
        }
    }

} // namespace chestnut::engine
