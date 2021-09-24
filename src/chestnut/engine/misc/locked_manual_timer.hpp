#ifndef __CHESTNUT_ENGINE_LOCKED_MANUAL_TIMER_H__
#define __CHESTNUT_ENGINE_LOCKED_MANUAL_TIMER_H__

#include "manual_timer.hpp"

namespace chestnut
{
    /**
     * @brief A timer class, which objects get updated (ticked) using extrnal delta time value and tick only in given time interval.
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick()
     * and pass it the elapsed time value. If it returns true, timer time reached the next interval and timer ticked.
     * Timer time here is a multiple of timer interval (until reset() is called).
     */
    class CLockedManualTimer : public CManualTimer
    {
    protected:
        // planned next interval tick of the timer
        uint64_t m_nextRelativeTick;
        // a tick obtained from latest tick() call which may or may not have been reached the interval
        uint64_t m_currentIntermediaryRelativeTick;

        // desired interval between ticks in seconds
        float m_updateIntervalInSeconds;
        // desired interval between ticks in microseconds
        uint32_t m_updateIntervalInMicroseconds;
        // a flag to tell whether user wants this timer to tick only once or more
        bool m_isRepeating;

    public:
        /**
         * @brief Construct a new CLockedManualTimer object
         * 
         * @param id identifier of the timer
         * @param updateIntervalInSeconds timer's tick interval in seconds
         * @param isRepeating whether timer should tick only once or unlimited times
         */
        CLockedManualTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating = false );

        float getUpdateIntervalInSeconds();
        bool getIsRepeating();

        void reset() override;

        /* Tick the timer using delta time in miliseconds. Returns true if managed to perform a tick i.e. if timer
         * was started
         * AND
         * is a repeating timer OR isn't repeating, but there hasn't been a successful tick yet 
         * AND
         * the time since the previous successful tick is equal to or greater than the timer interval */
        bool tick( float dt ) override;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_ENGINE_LOCKED_MANUAL_TIMER_H__