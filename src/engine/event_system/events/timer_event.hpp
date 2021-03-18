#ifndef __CHESTNUT_TIMER_EVENT_H__
#define __CHESTNUT_TIMER_EVENT_H__

#include "../event_base.hpp"
#include "engine/misc/locked_timer.hpp"

namespace chestnut
{
    struct STimerEvent : SEvent
    {
        timerid_t timerID;
        float timerTimeInSeconds;
        float timerIntervalInSeconds;
        bool isTimerRepeating;

        const std::string getName() override { return "TimerEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_EVENT_H__