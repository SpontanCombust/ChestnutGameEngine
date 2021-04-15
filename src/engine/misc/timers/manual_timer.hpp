#ifndef __CHESTNUT_MANUAL_TIMER_H__
#define __CHESTNUT_MANUAL_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    /**
     * @brief A timer class, which objects get updated (ticked) using extrnal delta time value
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick()
     * and pass it the elapsed time value. If it returns true, timer ticked.
     * Total timer time here is the sum of all delta times provided (until reset() is called).
     */
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