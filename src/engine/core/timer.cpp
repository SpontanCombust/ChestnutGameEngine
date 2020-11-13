#include "engine/core/timer.hpp"

namespace chestnut
{
    CTimer::CTimer( uint32_t interval, bool isRepeating )
    : m_alarmInterval( interval ), m_isRepeating( isRepeating )
    {
        reset( true );
        m_wasStarted = false;
    }

    void CTimer::reset( bool init )
    {
        if( !init )
        {
            m_startTick = SDL_GetTicks();
            m_currentTick = m_startTick;
        }
        m_lastAlarmTick = 0;
        m_lastPauseTick = 0;
        m_pausedTicks = 0;

        m_isPaused = false;
        m_isAlarmOnCurrentTick = false;
    }

    void CTimer::start()
    {
        if( !m_wasStarted )
        {
            m_startTick = SDL_GetTicks();
            m_currentTick = m_startTick;
            m_wasStarted = true;
        }
    }

    void CTimer::pause() 
    {
        m_isPaused = true;
        m_lastPauseTick = SDL_GetTicks();
    }

    void CTimer::unpause() 
    {
        m_isPaused = false;
        m_pausedTicks += SDL_GetTicks() - m_lastPauseTick;
    }

    uint32_t CTimer::getCurrentTicks() 
    {
        return m_currentTick;
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
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_lastAlarmTick == 0 ) ) )
        {
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

            return m_isAlarmOnCurrentTick;
        }
        
        return false;
    }

} // namespace chestnut
