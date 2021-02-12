#ifndef __CHESTNUT_KEYBOARD_EVENT_H__
#define __CHESTNUT_KEYBOARD_EVENT_H__

#include "../event_base.hpp"

#include <SDL2/SDL_events.h>

namespace chestnut
{
    struct SKeyboardEvent : SEvent
    {
        bool isPressed;
        SDL_Keycode keycode;
        uint16_t modifiers;

        const std::string getName() override { return "KeyboardEvent"; }
    };
    
} // namespace chestnut

#endif // __CHESTNUT_KEYBOARD_EVENT_H__