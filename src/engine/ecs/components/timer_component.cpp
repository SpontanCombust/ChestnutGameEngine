#include "timer_component.hpp"

namespace chestnut
{   
    STimerComponent::STimerComponent()
    {
        shouldDeleteTimersOnComponentDestroy = false;
        timerList.clear();
    }

    STimerComponent::STimerComponent( bool _shouldDeleteTimersOnComponentDestroy ) 
    {
        shouldDeleteTimersOnComponentDestroy = _shouldDeleteTimersOnComponentDestroy;
        timerList.clear();
    }

    STimerComponent::~STimerComponent() 
    {
        if( shouldDeleteTimersOnComponentDestroy )
        {
            for( CLockedTimer *timer : timerList )
            {
                delete timer;
                timer = nullptr;
            }
        }

        timerList.clear();
    }

} // namespace chestnut
