#ifndef __CHESTNUT_MANUAL_TIMER_H__
#define __CHESTNUT_MANUAL_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    /**
     * @brief A timer class, which objects get updated (ticked) using external delta time value
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

        void reset() override;

        // Tick the timer using delta time in seconds. 
        // Returns true only if performed a tick successfuly; here always if timer was started
        virtual bool tick( float dt );
    };
    
} // namespace chestnut


#endif // __CHESTNUT_MANUAL_TIMER_H__