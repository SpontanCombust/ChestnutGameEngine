#ifndef __CHESTNUT_MOUSE_MOTION_EVENT_H__
#define __CHESTNUT_MOUSE_MOTION_EVENT_H__

#include "../event_base.hpp"
#include "engine/maths/vector.hpp"

#include <SDL2/SDL_events.h>

namespace chestnut
{
    struct SMouseMotionEvent : SEvent
    {
        Vector2i pos;
        Vector2i motion;

        const std::string getName() override { return "MouseMotionEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_MOTION_EVENT_H__