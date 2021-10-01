#ifndef __CHESTNUT_ENGINE_TIMER_H__
#define __CHESTNUT_ENGINE_TIMER_H__

#include "../types.hpp"

#include <cstdint>

namespace chestnut::engine
{
    // A timer interface
    class ITimer
    {
    protected:
        // inner state vars //

        // number of microseconds since the start of the timer to the current tick
        uint64_t m_currentRelativeTick;
        // number of microseconds since the start of the timer to the tick before the current tick
        uint64_t m_lastRelativeTick;

        bool m_wasStarted;


        // user defined, constant properties //

        // ID given to a timer
        timerid_t m_timerID;

    public:
        ITimer( timerid_t id );
        virtual ~ITimer() = default;

        timerid_t getID();

        void start();

        virtual void reset() = 0;


        // Get number of microseconds since timer start
        uint64_t getElapsedTimeInMicroseconds();
        // Get number of miliseconds since timer start
        uint64_t getElapsedTimeInMiliseconds();
        // Get number of seconds since timer start
        double getElapsedTimeInSeconds();
        // Return time between current and previous successful tick in seconds
        float getDeltaTime();
        // Inverse of the delta time
        float getUpdatesPerSec();
    };
    
} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TIMER_H__