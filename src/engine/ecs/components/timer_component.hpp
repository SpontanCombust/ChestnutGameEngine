#ifndef __CHESTNUT_TIMER_COMPONENT_H__
#define __CHESTNUT_TIMER_COMPONENT_H__

#include "../component.hpp"
#include "engine/misc/timers/locked_manual_timer.hpp"
#include "engine/event_system/event_manager.hpp"

#include <vector>

namespace chestnut
{
    struct STimerComponent : IComponent
    {
        std::vector< CLockedManualTimer > vTimers;

        ~STimerComponent();

        timerid_t addTimer( float updateIntervalSec, bool isRepeating = false );
        bool removeTimer( timerid_t id );
        void removeTimers();

    private:
        static timerid_t m_timerIDAccumulator;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_COMPONENT_H__