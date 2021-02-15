#ifndef __CHESTNUT_EVENT_DRIVEN_SYSTEM_H__
#define __CHESTNUT_EVENT_DRIVEN_SYSTEM_H__

#include "../system.hpp"
#include "engine/event_system/event_manager.hpp"

#include <queue>

namespace chestnut
{
    class IEventDrivenSystem : public ISystem
    {
    protected:
        std::queue< SEvent* > m_localEventQueue;

    public:
        virtual bool needsToRaiseEvents() = 0;
        virtual void raiseEvents( CEventManager& eventManagerRef ) = 0;
        
        ~IEventDrivenSystem() {}
    };

} // namespace chestnut


#endif // __CHESTNUT_EVENT_DRIVEN_SYSTEM_H__