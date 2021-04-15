#include "manual_timer.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{    
    CManualTimer::CManualTimer( timerid_t id ) 
    : ITimer( id ) 
    {
        reset( true );
        m_wasStarted = false;
    }

    void CManualTimer::reset( bool init ) 
    {
        if( !init )
        {
            m_currentRelativeTick = m_lastRelativeTick = 0;
        }
        m_tickCount = 0;
    }

    bool CManualTimer::tick( uint32_t dt ) 
    {
        if( !m_wasStarted )
        {
            LOG_CHANNEL( "MANUAL_TIMER", "Warning! Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        if( dt > 0 )
        {
            m_lastRelativeTick = m_currentRelativeTick;
            m_currentRelativeTick += dt;
            m_tickCount++;

            return true;
        }

        return false;
    }

} // namespace chestnut
