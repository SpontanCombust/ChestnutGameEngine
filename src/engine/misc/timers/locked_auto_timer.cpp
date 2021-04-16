#include "locked_auto_timer.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    CLockedAutoTimer::CLockedAutoTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating )
    : CAutoTimer( id )
    {
        reset( true );
        
        if( updateIntervalInSeconds >= 0.001f )
        {
            m_updateIntervalInSeconds = updateIntervalInSeconds;
        }
        else
        {
            m_updateIntervalInSeconds = 0.001f;
        }
        
        m_isRepeating = isRepeating;
        m_shouldThreadWaitForTimer = false;
    }

    float CLockedAutoTimer::getUpdateIntervalInSeconds() 
    {
        return m_updateIntervalInSeconds;
    }

    bool CLockedAutoTimer::getIsRepeating() 
    {
        return m_isRepeating;
    }

    void CLockedAutoTimer::reset( bool init )
    {
        if( !init )
        {
            m_startTick = SDL_GetTicks();
            m_currentRelativeTick = m_lastRelativeTick = 0;
            m_nextRelativeTick = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );
        }
        m_tickCount = 0;
    }

    void CLockedAutoTimer::toggleThreadWaitingForTimerInterval( bool toggle ) 
    {
        m_shouldThreadWaitForTimer = toggle;
    }

    bool CLockedAutoTimer::tick() 
    {
        if( !m_wasStarted )
        {
            LOG_CHANNEL( "LOCKED_AUTO_TIMER", "Warning! Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }
        
        if( m_isRepeating || ( !m_isRepeating && m_tickCount == 0 ) )
        {
            uint32_t currentIntermediaryRelativeTick;
            uint32_t updateIntervalInMs;
            uint32_t timeToNextUpdate;
            bool shouldDelay;

            currentIntermediaryRelativeTick = SDL_GetTicks() - m_startTick;
            updateIntervalInMs = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );

            timeToNextUpdate = 0;
            shouldDelay = false;

            if( m_shouldThreadWaitForTimer && currentIntermediaryRelativeTick < m_nextRelativeTick )
            {
                shouldDelay = true;
                // it's bound to be a positive number
                timeToNextUpdate = m_nextRelativeTick - currentIntermediaryRelativeTick;
            }

            if( shouldDelay )
            {
                SDL_Delay( timeToNextUpdate );
                currentIntermediaryRelativeTick += timeToNextUpdate;
            }

            if( currentIntermediaryRelativeTick >= m_nextRelativeTick )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = currentIntermediaryRelativeTick;
                m_nextRelativeTick = currentIntermediaryRelativeTick + updateIntervalInMs;
                m_tickCount++;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut
