#ifndef __CHESTNUT_MOUSE_MOTION_EVENT_H__
#define __CHESTNUT_MOUSE_MOTION_EVENT_H__

#include "../event_base.hpp"
#include "engine/maths/vector2.hpp"

#include <SDL2/SDL_events.h>

namespace chestnut
{
    struct SMouseMotionEvent : SEvent
    {
        vec2i pos;
        vec2i motion;

        const std::string getName() override { return "MouseMotionEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_MOTION_EVENT_H__