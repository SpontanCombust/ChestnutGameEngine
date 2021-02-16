#ifndef __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__
#define __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__

#include "engine/event_system/event_manager.hpp"

#include <list>

namespace chestnut
{
    class CListenerRegisteringSystem
    {
    protected:
        std::list< SEventListener > m_listenersToBeRegistered;

    public:
        virtual bool needsToRegisterListeners();
        virtual void registerListeners( CEventManager& eventManagerRef );

        virtual ~CListenerRegisteringSystem() {}
    };

} // namespace chestnut

#endif // __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__