#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/misc/locked_manual_timer.hpp"

#include <vector>

namespace chestnut::engine
{
    struct CTimerComponent
    {
        std::vector< CLockedManualTimer > vTimers;

        CHESTNUT_API timerid_t addTimer( float updateIntervalSec, bool isRepeating = false );
        CHESTNUT_API bool removeTimer( timerid_t id );
        CHESTNUT_API void removeTimers();
    };

} // namespace chestnut::engine
