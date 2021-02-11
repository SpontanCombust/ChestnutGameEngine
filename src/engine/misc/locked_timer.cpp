#include "locked_timer.hpp"

namespace chestnut
{
    CLockedTimer::CLockedTimer( timer_id_t id, float interval, bool isRepeating )
    :   CTimer( id ), m_updateIntervalInSeconds( interval ), m_isRepeating( isRepeating )
    {
        reset( true );
    }

    float CLockedTimer::getUpdateIntervalInSeconds() 
    {
        return m_updateIntervalInSeconds;
    }

    bool CLockedTimer::getIsRepeating() 
    {
        return m_isRepeating;
    }

    bool CLockedTimer::update( bool shouldStartIfDidntAlready ) 
    {
        if( shouldStartIfDidntAlready )
        {
            start();
        }
        
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_updateCount == 0 ) ) )
        {
            uint32_t currentTestTick = SDL_GetTicks() - m_startTick - m_pausedTicks;
            uint32_t timeSinceLastUpdate = currentTestTick - m_currentTick;
            if( timeSinceLastUpdate >= ( m_updateIntervalInSeconds * 1000.f ) )
            {
                m_lastTick = m_currentTick;
                m_currentTick = currentTestTick;
                m_updateCount++;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut
