#ifndef __CHESTNUT_ENGINE_TIMER_EVENT_H__
#define __CHESTNUT_ENGINE_TIMER_EVENT_H__

#include "../../types.hpp"

namespace chestnut
{
    struct STimerEvent
    {
        timerid_t timerID;
        double timerTimeInSeconds;
        float timerIntervalInSeconds;
        bool isTimerRepeating;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_TIMER_EVENT_H__