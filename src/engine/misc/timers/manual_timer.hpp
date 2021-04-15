#ifndef __CHESTNUT_MANUAL_TIMER_H__
#define __CHESTNUT_MANUAL_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    class CManualTimer : public ITimer
    {
    public:
        CManualTimer( timerid_t id );

        void reset( bool init = false ) override;

        // Tick the timer using delta time in miliseconds. 
        // Returns true only if detected time advancing since last tick.
        virtual bool tick( uint32_t dt );
    };
    
} // namespace chestnut


#endif // __CHESTNUT_MANUAL_TIMER_H__