#include "chestnut/engine/ecs_impl/event_listener_guard.hpp"

#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
{    
    CEventListenerGuard::CEventListenerGuard() 
    {
        m_listener = nullptr;
        m_eventManagerPtr = nullptr;
    }

    CEventListenerGuard::CEventListenerGuard( IEventListener* listener, CEventManager* eventManagerPtr ) 
    {
        m_listener = listener;
        m_eventManagerPtr = eventManagerPtr;
    }

    CEventListenerGuard::~CEventListenerGuard() 
    {
        if( m_listener )
        {
            if( m_eventManagerPtr )
            {
                m_eventManagerPtr->unregisterListener( m_listener );
            }

            delete m_listener;
        }
    }

    void CEventListenerGuard::reset( IEventListener* listener, CEventManager* eventManagerPtr ) 
    {
        m_listener = listener;
        m_eventManagerPtr = eventManagerPtr;

        if( !eventManagerPtr )
        {
            LOG_WARNING( "Passed a null event manager pointer. Stored listener won't be able to be auto-unregistered."
                         "If this listener is registered somewhere, not unregistering it manually can cause a crash later if the listener is bound to a object method!" );
        }
    }

    IEventListener* CEventListenerGuard::get() const
    {
        return m_listener;
    }

} // namespace chestnut::engine
