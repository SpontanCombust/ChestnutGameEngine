#ifndef __CHESTNUT_KEYBOARD_EVENT_H__
#define __CHESTNUT_KEYBOARD_EVENT_H__

#include "../event_base.hpp"
#include "engine/libs.hpp"

namespace chestnut
{
    struct SKeyboardEvent : SEvent
    {
        bool isPressed;
        SDL_Keycode button;
        uint16_t modifiers;

        const std::string getName() override { return "KeyboardEvent"; }
    };
    
} // namespace chestnut

#endif // __CHESTNUT_KEYBOARD_EVENT_H__