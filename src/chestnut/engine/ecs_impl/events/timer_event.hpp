#ifndef __CHESTNUT_ENGINE_TIMER_EVENT_H__
#define __CHESTNUT_ENGINE_TIMER_EVENT_H__

#include "../event.hpp"
#include "../../types.hpp"

namespace chestnut
{
    struct STimerEvent : SEvent
    {
        timerid_t timerID;
        float timerTimeInSeconds;
        float timerIntervalInSeconds;
        bool isTimerRepeating;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_TIMER_EVENT_H__