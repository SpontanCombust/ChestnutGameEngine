#ifndef __CHESTNUT_TIMER_H__
#define __CHESTNUT_TIMER_H__

#include <SDL2/SDL_timer.h>

#include <cstdint>

namespace chestnut
{
    class CTimer
    {
    protected:
        // inner state vars //

        // the number of updated made on the timer
        uint64_t m_updateCount;
        // tick when timer was started
        uint32_t m_startTick;
        // tick since timer started minus paused ticks (current internal tick)
        uint32_t m_currentTick;
        // tick from the previous update
        uint32_t m_lastTick;
        // tick when timer was last time paused
        uint32_t m_lastPauseTick;
        // amount of ticks while the timer was paused
        uint32_t m_pausedTicks;

        bool m_wasStarted;
        bool m_isPaused;


        // user defined, constant properties //

        // ID given to a timer
        const int m_timerID;

    public:
        CTimer( int id );

        int getID();

        virtual void reset( bool init = false );
        virtual void start();
        
        void pause();
        void unpause();

        bool isPaused();

        // get number of miliseconds since timer start
        uint32_t getCurrentTimeInMiliseconds();
        // get number of seconds since timer start
        float getCurrentTimeInSeconds();
        /* return time between current and previous successful updates in seconds
         * Note that with update rate greater than 1000 per second it will return 0 most of the time due to timer precision limitation */
        float getDeltaTime();
        // return average number of updates per second
        float getAvgUpdatesPerSec();

        // returns true if was started and isn't paused
        virtual bool update( bool shouldStartIfDidntAlready = true );

        virtual ~CTimer() {}
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TIMER_H__