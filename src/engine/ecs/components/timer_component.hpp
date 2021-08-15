#ifndef __CHESTNUT_TIMER_COMPONENT_H__
#define __CHESTNUT_TIMER_COMPONENT_H__

#include "../../misc/timers/locked_manual_timer.hpp"
#include "../../event_system/event_manager.hpp"

#include <chestnut/ecs/component.hpp>

#include <vector>

namespace chestnut
{
    struct CTimerComponent : public ecs::CComponent
    {
        std::vector< CLockedManualTimer > vTimers;

        ~CTimerComponent();

        timerid_t addTimer( float updateIntervalSec, bool isRepeating = false );
        bool removeTimer( timerid_t id );
        void removeTimers();

    private:
        static timerid_t m_timerIDAccumulator;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_COMPONENT_H__