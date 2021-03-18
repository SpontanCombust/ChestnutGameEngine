#ifndef __CHESTNUT_LOCKED_TIMER_H__
#define __CHESTNUT_LOCKED_TIMER_H__

#include "timer.hpp"

namespace chestnut
{
    // a timer that has a locked update rate per second
    class CLockedTimer : public CTimer
    {
    protected:
        // user defined, constant properties //

        // timer alarm interval in seconds
        const float m_updateIntervalInSeconds;
        // whether alarm should be raised multiple times
        const bool m_isRepeating;

    public:
        CLockedTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating = false );

        float getUpdateIntervalInSeconds();
        bool getIsRepeating();

        /* returns true if: 
         * was started
         * AND
         * isn't paused
         * AND
         * is a repeating timer OR isn't repeating, but there's hasn't been a successful update yet 
         * AND
         * the time since the previous successful update is equal to or greater than  */
        bool update( bool shouldStartIfDidntAlready = true ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_LOCKED_TIMER_H__