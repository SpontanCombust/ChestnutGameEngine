#ifndef __CHESTNUT_ENGINE_MOUSE_BUTTON_EVENT_H__
#define __CHESTNUT_ENGINE_MOUSE_BUTTON_EVENT_H__

#include "../event.hpp"
#include "../../maths/vector2.hpp"

namespace chestnut
{
    struct SMouseButtonEvent : SEvent
    {
        bool isPressed;
        uint8_t button;
        uint8_t clicksNum;
        vec2i clickPos;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_MOUSE_BUTTON_EVENT_H__