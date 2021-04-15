#include "locked_manual_timer.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{    
    CLockedManualTimer::CLockedManualTimer( timerid_t id, float updateIntervalInSeconds, bool isRepeating )
    : CManualTimer( id ) 
    {
        reset( true );
        m_updateIntervalInSeconds = updateIntervalInSeconds;
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

    void CLockedManualTimer::reset( bool init ) 
    {
        if( !init )
        {
            m_currentRelativeTick = m_lastRelativeTick = 0;
            m_nextRelativeTick = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );
            m_currentIntermediaryRelativeTick = 0;
        }
        m_tickCount = 0;
    }

    bool CLockedManualTimer::tick( uint32_t dt ) 
    {
        if( !m_wasStarted )
        {
            LOG_CHANNEL( "LOCKED_MANUAL_TIMER", "Warning! Trying to update a timer that wasn't started yet!" );
            return false;
        }
        
        if( dt > 0 && ( m_isRepeating || ( !m_isRepeating && m_tickCount == 0 ) ) )
        {
            uint32_t updateIntervalInMs;

            updateIntervalInMs = static_cast<uint32_t>( m_updateIntervalInSeconds * 1000.f );

            m_currentIntermediaryRelativeTick += dt;

            if( m_currentIntermediaryRelativeTick >= m_nextRelativeTick )
            {
                m_lastRelativeTick = m_currentRelativeTick;
                m_currentRelativeTick = m_nextRelativeTick;
                m_nextRelativeTick += updateIntervalInMs;
                m_tickCount++;
                return true;
            }
        }
        
        return false;
    }

} // namespace chestnut
