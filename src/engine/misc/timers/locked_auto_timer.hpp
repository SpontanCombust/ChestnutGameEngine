#ifndef __CHESTNUT_LOCKED_AUTO_TIMER_H__
#define __CHESTNUT_LOCKED_AUTO_TIMER_H__

#include "auto_timer.hpp"

namespace chestnut
{
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