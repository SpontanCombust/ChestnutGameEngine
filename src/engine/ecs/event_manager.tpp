namespace chestnut
{    
    template<typename EventType>
    void CEventManager::raiseEvent( const EventType& event ) 
    {
        std::type_index type = typeid(EventType);

        auto& vecListeners = m_mapEventTypeToVecListeners[ type ];

        if( !vecListeners.empty() )
        {
            // iterate using iterator type so we can erase a listener if its pointer is exprired
            for( auto weakIt = vecListeners.begin(); weakIt != vecListeners.end(); /*NOP*/ )
            {
                if( auto shared = weakIt->lock() )
                {
                    if( shared->isEnabled() )
                    {
                        CEventListener<EventType> *listenerCasted = static_cast< CEventListener<EventType> * >( shared.get() );

                        if( listenerCasted->testFilter( event ) )
                        {
                            listenerCasted->invokeConsumer( event );
                        }
                    }

                    weakIt++;
                }
                else
                {
                    weakIt = vecListeners.erase( weakIt );
                }
            }
        }
    }

} // namespace chestnut
