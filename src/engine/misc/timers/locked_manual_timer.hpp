#ifndef __CHESTNUT_LOCKED_MANUAL_TIMER_H__
#define __CHESTNUT_LOCKED_MANUAL_TIMER_H__

#include "manual_timer.hpp"

namespace chestnut
{
    class CLockedManualTimer : public CManualTimer
    {
    protected:
        // planned next interval tick of the timer
        uint32_t m_nextRelativeTick;
        // a tick obtained from latest tick() call which may or may not have been reached the interval
        uint32_t m_currentIntermediaryRelativeTick;

        // timer alarm interval in seconds
        float m_updateIntervalInSeconds;
        // whether alarm should be raised multiple times
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

        void reset( bool init = false ) override;

        /* Tick the timer using delta time in miliseconds. Returns true if managed to perform a tick i.e. if timer
         * was started
         * AND
         * is a repeating timer OR isn't repeating, but there hasn't been a successful tick yet 
         * AND
         * the time since the previous successful tick is equal to or greater than the timer interval */
        bool tick( uint32_t dt ) override;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_LOCKED_MANUAL_TIMER_H__