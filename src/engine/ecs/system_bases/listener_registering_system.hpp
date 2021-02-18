#ifndef __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__
#define __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__

#include "engine/event_system/event_manager.hpp"

#include <list>
#include <utility>

namespace chestnut
{
    class CListenerRegisteringSystem
    {
    protected:
        std::list< SEventListener > m_listenersToBeRegistered;
        std::list< std::pair< eventListener_id_t, std::type_index > > m_listenersToBeUnregisteredDataPairs;

    public:
        virtual bool needsToManageListeners();
        virtual void manageListeners( CEventManager& eventManagerRef );

        virtual ~CListenerRegisteringSystem() {}
    };

} // namespace chestnut

#endif // __CHESTNUT_LISTENER_REGISTERING_SYSTEM_H__