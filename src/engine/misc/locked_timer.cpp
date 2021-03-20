#include "locked_timer.hpp"

namespace chestnut
{
    CLockedTimer::CLockedTimer( timerid_t id, float interval, bool isRepeating, bool sleepForIntervalDuration )
    :   CTimer( id )
    {
        m_updateIntervalInSeconds = interval;
        m_isRepeating = isRepeating;
        m_sleepThreadForIntervalDuration = sleepForIntervalDuration;
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

    void CLockedTimer::start() 
    {
        CTimer::start();
        m_nextRelativeTick = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );
    }

    bool CLockedTimer::update( bool shouldStartIfDidntAlready ) 
    {
        if( shouldStartIfDidntAlready && !m_wasStarted )
        {
            start();
        }
        
        if( m_wasStarted && !m_isPaused && ( m_isRepeating || ( !m_isRepeating && m_updateCount == 0 ) ) )
        {
            // current relative SDL tick since start
            uint32_t currentTestRelativeTick;
            uint32_t updateIntervalInMs;
            // ms left to next interval tick (BEWARE!!! the integer is unsigned!)
            uint32_t timeToNextUpdate;
            bool shouldDelay;


            currentTestRelativeTick = SDL_GetTicks() - m_startTick - m_pausedTicks;

            updateIntervalInMs = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );

            timeToNextUpdate = 0;
            shouldDelay = false;
            if( currentTestRelativeTick < m_nextRelativeTick && m_sleepThreadForIntervalDuration )
            {
                shouldDelay = true;
                // it's bound to be a positive number
                timeToNextUpdate = m_nextRelativeTick - currentTestRelativeTick;
            }

            if( shouldDelay )
            {
                SDL_Delay( timeToNextUpdate );
                currentTestRelativeTick += timeToNextUpdate;
            }
            if( currentTestRelativeTick >= m_nextRelativeTick )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = m_nextRelativeTick;
                m_nextRelativeTick += updateIntervalInMs;
                m_updateCount++;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut
