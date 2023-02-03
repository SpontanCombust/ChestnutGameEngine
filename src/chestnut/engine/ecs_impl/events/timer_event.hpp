#pragma once

#include "chestnut/engine/types.hpp"

namespace chestnut::engine
{
    struct STimerEvent
    {
        timerid_t timerID;
        double timerTimeInSeconds;
        float timerIntervalInSeconds;
        bool isTimerRepeating;
    };

} // namespace chestnut::engine
