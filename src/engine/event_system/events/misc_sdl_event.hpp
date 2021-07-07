#ifndef __CHESTNUT_MISC_SDL_EVENT_H__
#define __CHESTNUT_MISC_SDL_EVENT_H__

#include "../event_base.hpp"
#include "engine/libs.hpp"

namespace chestnut
{
    // A struct used to communicate SDL events that don't get any specific treatment by the engine
    struct SMiscSDLEvent : SEvent
    {
        SDL_Event sdlEvent;

        const std::string getName() override { return "SDLEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MISC_SDL_EVENT_H__