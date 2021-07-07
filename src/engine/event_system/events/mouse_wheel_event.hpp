#ifndef __CHESTNUT_MOUSE_WHEEL_EVENY_H__
#define __CHESTNUT_MOUSE_WHEEL_EVENY_H__

#include "../event_base.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/libs.hpp"

namespace chestnut
{
    struct SMouseWheelEvent : SEvent
    {
        vec2i scrollAmount;

        const std::string getName() override { return "MouseWheelEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_WHEEL_EVENY_H__