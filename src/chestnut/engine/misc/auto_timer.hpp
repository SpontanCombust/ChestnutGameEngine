#ifndef __CHESTNUT_AUTO_TIMER_H__
#define __CHESTNUT_AUTO_TIMER_H__

#include "timer.hpp"
#include "../types.hpp"

namespace chestnut
{
    /**
     * @brief A timer class which objects get updated (ticked) using std::chrono functionality
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick().
     * If it returns true, the timer ticked.
     * Total timer time here is the sum of all delta times provided (until reset() is called).
     */
    class CAutoTimer : public ITimer
    {
    protected:
        // tick value when timer was started
        uint64_t m_startAbsoluteTick;
        
    public:
        CAutoTimer( timerid_t id );

        void reset() override;

        // Returns true if managed to perform a tick
        // here it's true if timer was started
        virtual bool tick();

    protected:
        uint64_t getAbsoluteTimeInMicroseconds() const;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_AUTO_TIMER_H__