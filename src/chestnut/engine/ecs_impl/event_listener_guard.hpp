#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/event_listener.hpp"
#include "chestnut/engine/ecs_impl/event_manager.hpp"

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

