#include "locked_timer.hpp"

namespace chestnut
{
    CLockedTimer::CLockedTimer( timerid_t id, float interval, bool isRepeating )
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
        if( shouldStartIfDidntAlready && !m_wasStarted )
        {
            start();
        }
        
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_updateCount == 0 ) ) )
        {
            uint32_t currentTestRelativeTick = SDL_GetTicks() - m_startTick - m_pausedTicks;
            uint32_t timeSinceLastUpdate = currentTestRelativeTick - m_currentRelativeTick;
            uint32_t updateIntervalInMs = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );
            if( timeSinceLastUpdate >= updateIntervalInMs )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = currentTestRelativeTick;
                m_updateCount++;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut
