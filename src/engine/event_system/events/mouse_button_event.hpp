#ifndef __CHESTNUT_MOUSE_BUTTON_EVENT_H__
#define __CHESTNUT_MOUSE_BUTTON_EVENT_H__

#include "../event_base.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/libs.hpp"

namespace chestnut
{
    struct SMouseButtonEvent : SEvent
    {
        bool isPressed;
        uint8_t button;
        uint8_t clicksNum;
        vec2i clickPos;

        const std::string getName() override { return "MouseButtonEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_BUTTON_EVENT_H__