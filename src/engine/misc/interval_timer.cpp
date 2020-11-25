#include "engine/misc/interval_timer.hpp"

namespace chestnut
{
    CIntervalTimer::CIntervalTimer( int id, float interval, bool isRepeating )
    :   CTimer( id ), m_alarmInterval( interval ), m_isRepeating( isRepeating )
    {
        reset( true );
    }

    void CIntervalTimer::reset( bool init )
    {
        super::reset( init );
        m_isAlarmOnCurrentUpdate = false;
    }

    bool CIntervalTimer::isAlarmOnCurrentTick()
    {
        if( m_isPaused )
            return false;
        return m_isAlarmOnCurrentUpdate;
    }

    // returns whether alarm activates on current tick i.e. if the update is successful
    bool CIntervalTimer::update() 
    {
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_currentTick == m_startTick ) ) )
        {
            uint32_t currentTick = SDL_GetTicks() - m_startTick - m_pausedTicks;
            uint32_t timeSinceAlarm = currentTick - m_currentTick;
            if( timeSinceAlarm >= ( m_alarmInterval * 1000 ) )
            {
                m_lastTick = m_currentTick;
                m_currentTick = currentTick;
                m_isAlarmOnCurrentUpdate = true;
                m_updateCount++;
            }
            else
            {
                m_isAlarmOnCurrentUpdate = false;
            }

            return m_isAlarmOnCurrentUpdate;
        }
        
        return false;
    }

} // namespace chestnut
