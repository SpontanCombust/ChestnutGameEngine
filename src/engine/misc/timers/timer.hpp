#ifndef __CHESTNUT_TIMER_H__
#define __CHESTNUT_TIMER_H__

#include "engine/types.hpp"

#include <cstdint>

namespace chestnut
{
    // A timer interface
    class ITimer
    {
    protected:
        // inner state vars //

        // the number of timer ticks performed on the timer
        uint64_t m_tickCount;
        // relative tick value from the latest successful timer tick
        uint32_t m_currentRelativeTick;
        // relative tick value from the timer tick before the last successful one
        uint32_t m_lastRelativeTick;

        bool m_wasStarted;


        // user defined, constant properties //

        // ID given to a timer
        timerid_t m_timerID;

    public:
        ITimer( timerid_t id );

        timerid_t getID();

        void start();
        void resetAndStart();

        // Get number of miliseconds since timer start
        uint32_t getCurrentTimeInMiliseconds();
        // Get number of seconds since timer start
        float getCurrentTimeInSeconds();
        // Return time between current and previous successful tick in miliseconds
        uint32_t getDeltaTime();
        // Return average number of updates per second
        float getAvgUpdatesPerSec();

        virtual void reset( bool init = false ) = 0;

        virtual ~ITimer() = default;
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TIMER_H__