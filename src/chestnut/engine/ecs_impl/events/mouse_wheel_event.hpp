#ifndef __CHESTNUT_ENGINE_MOUSE_WHEEL_EVENT_H__
#define __CHESTNUT_ENGINE_MOUSE_WHEEL_EVENT_H__

#include "../event.hpp"
#include "../../maths/vector2.hpp"

namespace chestnut
{
    struct SMouseWheelEvent : SEvent
    {
        vec2i scrollAmount;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_MOUSE_WHEEL_EVENT_H__