#ifndef __CHESTNUT_TIMER_H__
#define __CHESTNUT_TIMER_H__

#include <SDL2/SDL_timer.h>

#include <cstdint>

namespace chestnut
{
    class CTimer
    {
        // inner state vars //

        // tick when timer was started
        uint32_t m_startTick;
        // tick since timer started minus paused ticks (current internal tick)
        uint32_t m_currentTick;
        // tick when last time alarm was activated
        uint32_t m_lastAlarmTick;
        // tick when timer was last time paused
        uint32_t m_lastPauseTick;
        // amount of ticks while the timer was paused
        uint32_t m_pausedTicks;

        bool m_wasStarted;
        bool m_isPaused;
        bool m_isAlarmOnCurrentTick;


        // user defined, constant properties //

        // timer alarm interval in ms
        const uint32_t m_alarmInterval;
        // whether alarm should be raised multiple times
        const bool m_isRepeating;

    public:
        // alarmInterval in ms
        CTimer( uint32_t alarmInterval, bool isRepeating = false );

        void reset( bool init = false );
        void start();
        void pause();
        void unpause();

        uint32_t getCurrentTicks();

        bool isPaused();
        bool isAlarmOnCurrentTick();

        bool update();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TIMER_H__