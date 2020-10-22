#ifndef __CHESTNUT_EVENTS_H__
#define __CHESTNUT_EVENTS_H__

#include <SDL2/SDL_timer.h>

#include <string>

namespace chestnut
{
    struct SEvent
    {
        std::string eventName;
        bool isHandled;
    };
    
    struct STimerEvent : SEvent
    {
        uint32_t deltaTime;
        bool isRepeating;
    };

} // namespace chestnut


#endif // __CHESTNUT_EVENTS_H__