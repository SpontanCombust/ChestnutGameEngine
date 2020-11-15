#include "engine/event_system/event_manager.hpp"

namespace chestnut
{
    void CEventManager::raiseEvent( SEvent *event ) 
    {
        if( !event )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to raise null event!" );
            return;
        }

        m_eventQueue.push( event );
    }
    
    void CEventManager::clearListeners() 
    {
        for( auto &pair : m_IDToListenerMap )
        {
            SEventListener listener = pair.second;

            delete listener.functionInvoker;

            if( listener.constraint )
                delete listener.constraint;
        }
        m_IDToListenerMap.clear();

        m_eventTypeToIDListMap.clear();
    }
    
    void CEventManager::clearEventQueue() 
    {
        while( !m_eventQueue.empty() )
        {
            SEvent *event = m_eventQueue.front();
            m_eventQueue.pop();
            delete event;
            event = nullptr;
        }
    }
    
    void CEventManager::delegateEvent( SEvent *event ) 
    {
        std::type_index tindex = std::type_index( typeid( *event ) );
        if( m_eventTypeToIDListMap.find( tindex ) != m_eventTypeToIDListMap.end() )
        {
            std::list< int > &typedIDList = m_eventTypeToIDListMap[ tindex ];

            for( const int &id : typedIDList )
            {
                SEventListener &listener = m_IDToListenerMap[ id ];

                if( listener.constraint )
                {
                    if( listener.constraint->verify( event ) )
                        listener.functionInvoker->invoke( event );
                }
                else
                    listener.functionInvoker->invoke( event );
            }
        }
    }

    void CEventManager::delegateEvents() 
    {
        SEvent *event;
        while( !m_eventQueue.empty() )
        {
            event = m_eventQueue.front();
            m_eventQueue.pop();
            delegateEvent( event );
            delete event;
            event = nullptr;
        }
    }

    void CEventManager::update( float deltaTime )
    {
        if( !m_eventQueue.empty() )
            delegateEvents();
    }

    CEventManager::~CEventManager() 
    {
        clearEventQueue();
        clearListeners();        
    }

} // namespace chestnut
