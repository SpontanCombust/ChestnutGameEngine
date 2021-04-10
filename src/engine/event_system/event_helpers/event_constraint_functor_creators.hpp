#ifndef __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__
#define __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__

#include "../events/events.hpp"

#include <functional>

namespace chestnut
{
    std::function< bool( const SKeyboardEvent& ) > keyboardEventConstraintFunc( SDL_Keycode button, bool checkIfPressedDown = true, bool shouldBePressedDown = true, bool checkModifiers = false, uint16_t modifiers = KMOD_NONE );

    std::function< bool( const SMouseButtonEvent& ) > mouseButtonEventConstraintFunc( uint8_t button, bool checkIfPressedDown = true, bool shouldBePressedDown = true, bool checkClickNum = false, uint8_t clickNum = 1 );

    std::function< bool( const SMouseWheelEvent& ) > mouseWheelEventConstraintFunc( bool shouldReactOnXScroll, bool shouldReactOnYScroll );

    std::function< bool( const STimerEvent& ) > timerEventConstraintFunc( timerid_t timerID );

} // namespace chestnut

#endif // __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__