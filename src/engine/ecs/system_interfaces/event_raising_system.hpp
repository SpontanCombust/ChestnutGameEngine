#ifndef __CHESTNUT_EVENT_RAISING_SYSTEM_H__
#define __CHESTNUT_EVENT_RAISING_SYSTEM_H__

#include "engine/event_system/event_manager.hpp"

namespace chestnut
{
    class IEventRaisingSystem
    {
    public:
        virtual bool needsToRaiseEvents() = 0;
        virtual void raiseEvents( CEventManager& eventManagerRef ) = 0;
        
        ~IEventRaisingSystem() {}
    };

} // namespace chestnut

#endif // __CHESTNUT_EVENT_RAISING_SYSTEM_H__