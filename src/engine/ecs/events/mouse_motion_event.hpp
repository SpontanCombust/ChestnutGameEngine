#ifndef __CHESTNUT_MOUSE_MOTION_EVENT_H__
#define __CHESTNUT_MOUSE_MOTION_EVENT_H__

#include "../event.hpp"
#include "../../maths/vector2.hpp"
#include "../../libs.hpp"

namespace chestnut
{
    struct SMouseMotionEvent : SEvent
    {
        vec2i pos;
        vec2i motion;
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_MOTION_EVENT_H__