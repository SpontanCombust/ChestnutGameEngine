#ifndef __CHESTNUT_MOUSE_WHEEL_EVENY_H__
#define __CHESTNUT_MOUSE_WHEEL_EVENY_H__

#include "../event_base.hpp"
#include "engine/maths/vector.hpp"

#include <SDL2/SDL_events.h>

namespace chestnut
{
    struct SMouseWheelEvent : SEvent
    {
        Vector2i scrollAmount;

        const std::string getName() override { return "MouseWheelEvent"; }
    };

} // namespace chestnut

#endif // __CHESTNUT_MOUSE_WHEEL_EVENY_H__