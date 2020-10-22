#include "engine/core/timer.hpp"

namespace chestnut
{
    void CTimer::reset( bool init )
    {
        if( !init )
        {
            m_startTicks = SDL_GetTicks();
            m_currentTicks = m_startTicks;
        }
        m_lastAlarmTicks = 0;
        m_isPaused = false;
        m_isAlarmOnCurrentTick = false;
    }

    void CTimer::start()
    {
        m_startTicks = SDL_GetTicks();
        m_currentTicks = m_startTicks;
        m_wasStarted = true;
    }

    CTimer::CTimer( uint32_t interval, bool isRepeating )
    {
        reset( true );
        m_alarmInterval = interval;
        m_isRepeating = isRepeating;
    }

    uint32_t CTimer::getCurrentTicks() 
    {
        return m_currentTicks;
    }

    void CTimer::setPaused( bool paused ) 
    {
        m_isPaused = paused;
    }

    bool CTimer::isPaused() 
    {
        return m_isPaused;
    }

    bool CTimer::isAlarmOnCurrentTick()
    {
        return m_isAlarmOnCurrentTick;
    }

    // returns whether alarm activates on current tick
    bool CTimer::update() 
    {
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_lastAlarmTicks == 0 ) ) )
        {
            m_currentTicks = SDL_GetTicks() - m_startTicks;
            uint32_t timeSinceAlarm = m_currentTicks - m_lastAlarmTicks;
            if( timeSinceAlarm >= m_alarmInterval )
            {
                //??? might need tweaking. To the average of last and latest possible alarm tick?
                m_lastAlarmTicks += m_alarmInterval * ( timeSinceAlarm / m_alarmInterval );
                m_isAlarmOnCurrentTick = true;
            }
            else
            {
                m_isAlarmOnCurrentTick = false;
            }

            return m_isAlarmOnCurrentTick;
        }
        
        return false;
    }

} // namespace chestnut
