#ifndef __CHESTNUT_TIMER_H__
#define __CHESTNUT_TIMER_H__

#include <SDL2/SDL_timer.h>

#include <cstdint>

namespace chestnut
{
    class CTimer
    {
        uint32_t m_startTicks;
        uint32_t m_lastAlarmTicks;
        uint32_t m_currentTicks;
        uint32_t m_alarmInterval;
        bool m_wasStarted;
        bool m_isRepeating;
        bool m_isPaused;
        bool m_isAlarmOnCurrentTick;

    public:
        void reset( bool init = false );
        void start();

        CTimer( uint32_t alarmInterval, bool isRepeating = false );
        
        uint32_t getCurrentTicks();
        void setPaused( bool paused );
        bool isPaused();
        bool isAlarmOnCurrentTick();
        bool update();
    };
    
} // namespace chestnut

#endif // __CHESTNUT_TIMER_H__