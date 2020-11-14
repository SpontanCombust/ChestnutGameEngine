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
        for( auto &pair : m_listenersMap )
        {
            std::vector< IFunctionInvoker* > *typedListeners = pair.second;

            for( IFunctionInvoker *listener : ( *typedListeners ) )
            {
                delete listener;
                listener = nullptr;
            }
            typedListeners->clear();

            delete typedListeners;
            typedListeners = nullptr;
        }
        m_listenersMap.clear();
    }
    
    void CEventManager::clearEventQueue() 
    {
        while( !m_eventQueue.empty() )
        {
            SEvent *event = m_eventQueue.front();
            delete event;
            event = nullptr;

            m_eventQueue.pop();
        }
    }
    
    bool CEventManager::delegateEvent( SEvent *event ) 
    {
        const char* evName = event->getName();
        std::type_index tindex = std::type_index( typeid( *event ) );
        if( m_listenersMap.find( tindex ) != m_listenersMap.end() )
        {
            std::vector< IFunctionInvoker* > *typedListeners = m_listenersMap[ tindex ];

            for( IFunctionInvoker *listener : ( *typedListeners ) )
            {
                listener->invoke( event );

                // if event function illegaly freed the pointer
                if( !event )
                {
                    LOG_CHANNEL( "EVENT_MANAGER", "(" << evName << ") " << " ptr illegally deleted by event function!" );
                    return false;
                }
            }

            return true;
        }
        return false;
    }

    void CEventManager::delegateEvents() 
    {
        SEvent *event;
        while( !m_eventQueue.empty() )
        {
            event = m_eventQueue.front();
            m_eventQueue.pop();
            // if event ptr hasn't been deleted along the way
            if( delegateEvent( event ) )
                // free after it has been passed to all event functions
                delete event;
        }
    }

    void CEventManager::update( float deltaTime )
    {
        delegateEvents();
    }

    CEventManager::~CEventManager() 
    {
        clearEventQueue();
        clearListeners();        
    }

} // namespace chestnut
