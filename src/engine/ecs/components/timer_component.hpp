#ifndef __CHESTNUT_TIMER_COMPONENT_H__
#define __CHESTNUT_TIMER_COMPONENT_H__

#include "../component.hpp"
#include "engine/misc/locked_timer.hpp"
#include "engine/event_system/event_manager.hpp"

#include <list>
#include <unordered_map>

namespace chestnut
{
    struct STimerComponent
    {
        std::list< CLockedTimer* > timerList;
        std::unordered_map< timer_id_t, eventListener_id_t > timerIDToListenerIDMap;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_COMPONENT_H__