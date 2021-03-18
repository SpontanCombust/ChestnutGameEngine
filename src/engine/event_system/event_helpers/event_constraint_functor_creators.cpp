#include "event_constraint_functor_creators.hpp"

namespace chestnut
{
    std::function< bool( const SKeyboardEvent& ) > getKeyboardEventConstraintFunctor( SDL_Keycode button, bool checkIfPressed, bool shouldBePressed, bool checkModifiers, uint16_t modifiers )
    {
        return [=]( const SKeyboardEvent& event ) -> bool
        {
            if( event.button != button )
            {
                return false;
            }
            else if( checkIfPressed && event.isPressed != shouldBePressed )
            {
                return false;
            }
            else if( checkModifiers && event.modifiers != modifiers )
            {
                return false;
            }

            return true;
        };
    }

    std::function< bool( const SMouseButtonEvent& ) > getMouseButtonEventConstraintFunctor( uint8_t button, bool checkIfPressed, bool shouldBePressed, bool checkClickNum, uint8_t clickNum )
    {
        return [=]( const SMouseButtonEvent& event ) -> bool
        {
            if( event.button != button )
            {
                return false;
            }
            else if( checkIfPressed && event.isPressed != shouldBePressed )
            {
                return false;
            }
            else if( checkClickNum && event.clicksNum != clickNum )
            {
                return false;
            }

            return true;
        };
    }

    std::function< bool( const SMouseWheelEvent& ) > getMouseWheelEventConstraintFunctor( bool shouldReactOnXScroll, bool shouldReactOnYScroll )
    {
        return [=]( const SMouseWheelEvent& event ) -> bool
        {
            if( ( shouldReactOnXScroll && event.scrollAmount.x != 0 ) || ( shouldReactOnYScroll && event.scrollAmount.y != 0 ) )
            {
                return true;
            }

            return false;
        };
    }

    std::function< bool( const STimerEvent& ) > getTimerEventConstraintFunctor( timerid_t timerID )
    {
        return [=]( const STimerEvent& event ) -> bool
        {
            if( event.timerID == timerID )
            {
                return true;
            }

            return false;
        };
    }

} // namespace chestnut
