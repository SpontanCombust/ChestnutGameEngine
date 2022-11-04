#include "chestnut/engine/misc/locked_manual_timer.hpp"

#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
{    
    CLockedManualTimer::CLockedManualTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating )
    : CManualTimer( id ) 
    {
        m_nextRelativeTick = 0;
        m_currentIntermediaryRelativeTick = 0;

        m_updateIntervalInSeconds = updateIntervalInSeconds;
        m_updateIntervalInMicroseconds = static_cast<uint32_t>( updateIntervalInSeconds * 1000000.f );
        m_isRepeating = isRepeating;
    }

    float CLockedManualTimer::getUpdateIntervalInSeconds() 
    {
        return m_updateIntervalInSeconds;
    }

    bool CLockedManualTimer::getIsRepeating() 
    {
        return m_isRepeating;
    }

    void CLockedManualTimer::reset() 
    {
        m_currentRelativeTick = m_lastRelativeTick = 0;
        m_currentIntermediaryRelativeTick = 0;
        m_nextRelativeTick = m_updateIntervalInMicroseconds;
    }

    bool CLockedManualTimer::tick( float dt ) 
    {
        if( !m_wasStarted )
        {
            LOG_WARNING( "Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }
        
        if( m_isRepeating || ( !m_isRepeating && m_currentRelativeTick == 0 ) )
        {
            m_currentIntermediaryRelativeTick += static_cast<uint64_t>( dt * 1000000.f );

            if( m_currentIntermediaryRelativeTick >= m_nextRelativeTick )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = m_currentIntermediaryRelativeTick;
                m_nextRelativeTick += m_updateIntervalInMicroseconds;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut::engine
