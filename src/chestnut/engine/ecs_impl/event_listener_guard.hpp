#ifndef __CHESTNUT_ENGINE_EVENT_LISTENER_GUARD_H__
#define __CHESTNUT_ENGINE_EVENT_LISTENER_GUARD_H__

#include "chestnut/engine/macros.hpp"
#include "event_listener.hpp"
#include "event_manager.hpp"

namespace chestnut::engine
{
    // Class using RAII mechanism to automatically unregister and delete the event listener when the object goes out of scope
    class CHESTNUT_API CEventListenerGuard
    {
    private:
        CEventManager* m_eventManagerPtr;
        IEventListener* m_listener;

    public:
        CEventListenerGuard();
        // By passing a listener pointer, you hand over its ownership to the guard
        CEventListenerGuard( IEventListener* listener, CEventManager* eventManagerPtr );
        ~CEventListenerGuard();

        // By passing a listener pointer, you hand over its ownership to the guard
        void reset( IEventListener* listener, CEventManager* eventManagerPtr );
        IEventListener* get() const;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_EVENT_LISTENER_GUARD_H__