namespace chestnut
{    
    template<typename EventType>
    void CEventManager::raiseEvent( const EventType& event ) 
    {
        std::type_index type = typeid(EventType);

        auto& listNodes = m_mapEventTypeToListListenerNodes[ type ];

        if( !listNodes.empty() )
        {
            // iterate using iterator type so we can erase a listener if its pointer is exprired
            for( auto it = listNodes.begin(); it != listNodes.end(); /*NOP*/ )
            {
                if( auto itShared = it->weakPtr.lock() )
                {
                    if( itShared->isEnabled() )
                    {
                        CEventListener<EventType> *listenerCasted = static_cast< CEventListener<EventType> * >( itShared.get() );

                        listenerCasted->invokeHandlerIfFilterAccepts( event );
                    }

                    it++;
                }
                else
                {
                    it = listNodes.erase( it );
                }
            }
        }
    }

} // namespace chestnut
