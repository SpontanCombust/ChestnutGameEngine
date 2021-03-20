#ifndef __CHESTNUT_LOCKED_TIMER_H__
#define __CHESTNUT_LOCKED_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    // a timer that has a locked update rate per second
    class CLockedTimer : public CTimer
    {
    protected:
        // planned next interval tick of the timer
        uint32_t m_nextRelativeTick;
        // timer alarm interval in seconds
        float m_updateIntervalInSeconds;
        // whether alarm should be raised multiple times
        bool m_isRepeating;
        // whether timer should make the thread sleep until the next interval tick
        bool m_sleepThreadForIntervalDuration;

    public:
        /**
         * @brief Construct a new CLockedTimer object
         * 
         * @param id identifier of the timer
         * @param updateIntervalInSeconds timer's tick interval in seconds
         * @param isRepeating whether timer should tick only once or unlimited times
         * @param sleepThreadForIntervalDuration whether the timer should make the thread sleep for the duration of timer's tick (timer interval); use only with timers controlling game loop
         */
        CLockedTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating = false, bool sleepThreadForIntervalDuration = false );

        float getUpdateIntervalInSeconds();
        bool getIsRepeating();

        void start() override;

        /* returns true if: 
         * was started
         * AND
         * isn't paused
         * AND
         * is a repeating timer OR isn't repeating, but there's hasn't been a successful update yet 
         * AND
         * the time since the previous successful update is equal to or greater than  */
        bool update( bool startIfDidntAlready = true ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_LOCKED_TIMER_H__