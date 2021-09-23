#ifndef __CHESTNUT_MISC_SDL_EVENT_H__
#define __CHESTNUT_MISC_SDL_EVENT_H__

#include "../event.hpp"

#include <SDL2/SDL_events.h>

namespace chestnut
{
    // A struct used to communicate SDL events that don't get any specific treatment by the engine
    struct SMiscSDLEvent : SEvent
    {
        SDL_Event sdlEvent;
    };

} // namespace chestnut

#endif // __CHESTNUT_MISC_SDL_EVENT_H__