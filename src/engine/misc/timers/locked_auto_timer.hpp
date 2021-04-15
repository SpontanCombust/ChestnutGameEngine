#ifndef __CHESTNUT_LOCKED_AUTO_TIMER_H__
#define __CHESTNUT_LOCKED_AUTO_TIMER_H__

#include "auto_timer.hpp"

namespace chestnut
{
    /**
     * @brief A timer class which objects get updated (ticked) using SDL timer functionality and tick only in given tick interval.
     * 
     * @details
     * The timer counts time starting from the point of calling start(). To update it call tick().
     * If it returns true, timer time reached the next interval and timer ticked.
     * Timer time here is a multiple of timer interval (until reset() is called).
     * Supports making the thread wait until timer hits interval.
     */
    class CLockedAutoTimer : public CAutoTimer
    {
    protected:
        // planned next interval tick of the timer
        uint32_t m_nextRelativeTick;
        // timer alarm interval in seconds
        float m_updateIntervalInSeconds;
        // whether alarm should be raised multiple times
        bool m_isRepeating;
        // whether thread should be put to sleep when calling tick() until the interval is reached
        bool m_shouldThreadWaitForTimer;

    public:
        /**
         * @brief Construct a new CLockedAutoTimer object
         * 
         * @param id identifier of the timer
         * @param updateIntervalInSeconds timer's tick interval in seconds
         * @param isRepeating whether timer should tick only once or unlimited times
         */
        CLockedAutoTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating = false );

        float getUpdateIntervalInSeconds();
        bool getIsRepeating();

        void toggleThreadWaitingForTimerInterval( bool toggle );

        void reset( bool init = false ) override;

        /* Returns true if managed to perform a tick i.e. if timer
         * was started
         * AND
         * is a repeating timer OR isn't repeating, but there hasn't been a successful tick yet 
         * AND
         * the time since the previous successful tick is equal to or greater than the timer interval */
        bool tick() override;
    };
    
} // namespace chestnut


#endif // __CHESTNUT_LOCKED_AUTO_TIMER_H__