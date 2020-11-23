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

        uint32_t getCurrentTicks();
        uint32_t getDeltaTime();
        double getAvgUpdatesPerSec();

        virtual bool update();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TIMER_H__