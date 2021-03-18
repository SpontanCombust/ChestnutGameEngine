#ifndef __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__
#define __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__

#include "../events/events.hpp"

#include <functional>

namespace chestnut
{
    std::function< bool( const SKeyboardEvent& ) > getKeyboardEventConstraintFunctor( SDL_Keycode button, bool checkIfPressed = true, bool shouldBePressed = true, bool checkModifiers = false, uint16_t modifiers = KMOD_NONE );

    std::function< bool( const SMouseButtonEvent& ) > getMouseButtonEventConstraintFunctor( uint8_t button, bool checkIfPressed = true, bool shouldBePressed = true, bool checkClickNum = false, uint8_t clickNum = 1 );

    std::function< bool( const SMouseWheelEvent& ) > getMouseWheelEventConstraintFunctor( bool shouldReactOnXScroll, bool shouldReactOnYScroll );

    std::function< bool( const STimerEvent& ) > getTimerEventConstraintFunctor( timerid_t timerID );

} // namespace chestnut

#endif // __CHESTNUT_EVENT_CONSTRAINT_FUNCTOR_CREATORS_H__