#pragma once

#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/misc/locked_manual_timer.hpp"

#include <vector>

namespace chestnut::engine
{
    struct CHESTNUT_API CTimerComponent
    {
        std::vector< CLockedManualTimer > vTimers;

        ~CTimerComponent();

        timerid_t addTimer( float updateIntervalSec, bool isRepeating = false );
        bool removeTimer( timerid_t id );
        void removeTimers();

    private:
        static timerid_t m_timerIDAccumulator;
    };

} // namespace chestnut::engine
