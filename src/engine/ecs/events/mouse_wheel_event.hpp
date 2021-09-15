#ifndef __CHESTNUT_MOUSE_WHEEL_EVENY_H__
#define __CHESTNUT_MOUSE_WHEEL_EVENY_H__

#include "../event.hpp"
#include "../../maths/vector2.hpp"

namespace chestnut
{
    struct SMouseWheelEvent : SEvent
    {
        vec2i scrollAmount;
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_WHEEL_EVENY_H__