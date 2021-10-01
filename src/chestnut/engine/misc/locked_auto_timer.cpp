#include "locked_auto_timer.hpp"

#include "../debug/log.hpp"

#include <thread>

namespace chestnut::engine
{
    CLockedAutoTimer::CLockedAutoTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating )
    : CAutoTimer( id )
    {
        m_updateIntervalInSeconds = updateIntervalInSeconds;
        m_updateIntervalInMicroseconds = static_cast<uint32_t>( updateIntervalInSeconds * 1000000.f );
        
        m_isRepeating = isRepeating;
        m_shouldThreadWaitForTimer = false;

        m_nextRelativeTick = 0;
    }

    float CLockedAutoTimer::getUpdateIntervalInSeconds() 
    {
        return m_updateIntervalInSeconds;
    }

    bool CLockedAutoTimer::getIsRepeating() 
    {
        return m_isRepeating;
    }

    void CLockedAutoTimer::reset()
    {
        m_startAbsoluteTick = getAbsoluteTimeInMicroseconds();
        m_currentRelativeTick = m_lastRelativeTick = 0;
        m_nextRelativeTick = m_updateIntervalInMicroseconds;
    }

    void CLockedAutoTimer::toggleThreadWaitingForTimerInterval( bool toggle ) 
    {
        m_shouldThreadWaitForTimer = toggle;
    }

    bool CLockedAutoTimer::tick() 
    {
        uint64_t measure = getAbsoluteTimeInMicroseconds();

        if( !m_wasStarted )
        {
            LOG_WARNING( "Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }
        
        if( m_isRepeating || ( !m_isRepeating && m_currentRelativeTick == 0 ) )
        {
            uint64_t currentIntermediaryRelativeTick = measure - m_startAbsoluteTick;

            if( currentIntermediaryRelativeTick >= m_nextRelativeTick )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = currentIntermediaryRelativeTick;
                m_nextRelativeTick = currentIntermediaryRelativeTick + m_updateIntervalInMicroseconds;

                return true;
            }
            else
            {
                if( m_shouldThreadWaitForTimer )
                {
                    uint32_t timeToNextTick = static_cast<uint32_t>( m_nextRelativeTick - currentIntermediaryRelativeTick );

                    std::this_thread::sleep_for( std::chrono::microseconds( timeToNextTick ) );

                    m_lastRelativeTick = m_currentRelativeTick;
                    m_currentRelativeTick = m_nextRelativeTick;
                    m_nextRelativeTick += m_updateIntervalInMicroseconds;

                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        
        return false;
    }

} // namespace chestnut::engine
