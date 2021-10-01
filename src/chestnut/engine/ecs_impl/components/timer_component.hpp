#ifndef __CHESTNUT_ENGINE_TIMER_COMPONENT_H__
#define __CHESTNUT_ENGINE_TIMER_COMPONENT_H__

#include "../../misc/locked_manual_timer.hpp"

#include <chestnut/ecs/component.hpp>

#include <vector>

namespace chestnut::engine
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

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TIMER_COMPONENT_H__