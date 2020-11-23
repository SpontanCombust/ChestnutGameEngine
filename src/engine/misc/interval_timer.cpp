#include "engine/misc/interval_timer.hpp"

namespace chestnut
{
    CIntervalTimer::CIntervalTimer( int id, uint32_t interval, bool isRepeating )
    :   CTimer( id ), m_alarmInterval( interval ), m_isRepeating( isRepeating )
    {
        reset( true );
    }

    void CIntervalTimer::reset( bool init )
    {
        super::reset( init );
        m_lastAlarmTick = 0;
        m_isAlarmOnCurrentTick = false;
    }

    bool CIntervalTimer::isAlarmOnCurrentTick()
    {
        return m_isAlarmOnCurrentTick;
    }

    // returns whether alarm activates on current tick
    bool CIntervalTimer::update() 
    {
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_lastAlarmTick == 0 ) ) )
        {
            m_lastTick = m_currentTick;
            m_currentTick = SDL_GetTicks() - m_startTick - m_pausedTicks;
            uint32_t timeSinceAlarm = m_currentTick - m_lastAlarmTick;
            if( timeSinceAlarm >= m_alarmInterval )
            {
                m_lastAlarmTick = m_currentTick;
                m_isAlarmOnCurrentTick = true;
            }
            else
            {
                m_isAlarmOnCurrentTick = false;
            }

            m_updateCount++;
            return m_isAlarmOnCurrentTick;
        }
        
        return false;
    }

} // namespace chestnut
