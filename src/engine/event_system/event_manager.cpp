#include "event_manager.hpp"

namespace chestnut
{
    SEventListener::SEventListener() 
    : eventTindex( TINDEX( void ) )
    {
        functionInvoker = nullptr;
        constraint = nullptr;
    }


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
        // For every listener, free the memory from the invoker and constraint
        for( auto &pair : m_IDToListenerMap )
        {
            SEventListener listener = pair.second;

            delete listener.functionInvoker;

            if( listener.constraint )
                delete listener.constraint;
        }

        // Clear maps from IDs and listener objects

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
        // Find the type of the event
        std::type_index tindex = TINDEX( *event );
        // Check if there are listeners with that type
        if( m_eventTypeToIDListMap.find( tindex ) != m_eventTypeToIDListMap.end() )
        {
            // Get list of listener IDs for that event type
            std::list< eventListener_id_t > &typedIDList = m_eventTypeToIDListMap[ tindex ];

            // Iterate over every ID in the list
            for( const eventListener_id_t &id : typedIDList )
            {
                // Get the specific listener
                SEventListener &listener = m_IDToListenerMap[ id ];

                if( listener.constraint )
                {
                    // If event doesn't fit constraint's demands, move onto next listener
                    if( !listener.constraint->verify( event ) )
                    {
                        continue;
                    }
                }
                
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
