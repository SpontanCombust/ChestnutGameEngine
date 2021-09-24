#ifndef __CHESTNUT_ENGINE_KEYBOARD_EVENT_H__
#define __CHESTNUT_ENGINE_KEYBOARD_EVENT_H__

#include "../event.hpp"

#include <SDL2/SDL_keyboard.h>

namespace chestnut
{
    struct SKeyboardEvent : SEvent
    {
        bool isPressed;
        SDL_Keycode button;
        uint16_t modifiers;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_ENGINE_KEYBOARD_EVENT_H__