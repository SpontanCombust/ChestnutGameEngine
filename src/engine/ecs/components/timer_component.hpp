#ifndef __CHESTNUT_TIMER_COMPONENT_H__
#define __CHESTNUT_TIMER_COMPONENT_H__

#include "../component.hpp"
#include "engine/misc/locked_timer.hpp"
#include "engine/event_system/event_manager.hpp"

#include <list>
#include <unordered_map>

namespace chestnut
{
    struct STimerComponent : IComponent
    {
        bool shouldDeleteTimersOnComponentDestroy;
        std::list< CLockedTimer* > timerList;

        STimerComponent();
        STimerComponent( bool _shouldDeleteTimersOnComponentDestroy );
        ~STimerComponent();
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_COMPONENT_H__