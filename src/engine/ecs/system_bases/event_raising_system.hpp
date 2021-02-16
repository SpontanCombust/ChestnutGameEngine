#ifndef __CHESTNUT_EVENT_RAISING_SYSTEM_H__
#define __CHESTNUT_EVENT_RAISING_SYSTEM_H__

#include "engine/event_system/event_manager.hpp"

#include <queue>

namespace chestnut
{
    class CEventRaisingSystem
    {
    protected:
        std::queue< SEvent* > m_localEventQueue;

    public:
        virtual bool needsToRaiseEvents();
        virtual void raiseEvents( CEventManager& eventManagerRef );
        
        virtual ~CEventRaisingSystem() {}
    };

} // namespace chestnut

#endif // __CHESTNUT_EVENT_RAISING_SYSTEM_H__