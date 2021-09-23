#include "manual_timer.hpp"

#include "../debug/debug.hpp"

namespace chestnut
{    
    CManualTimer::CManualTimer( timerid_t id ) 
    : ITimer( id ) 
    {
        
    }

    void CManualTimer::reset() 
    {
        m_currentRelativeTick = m_lastRelativeTick = 0;
    }

    bool CManualTimer::tick( float dt ) 
    {
        if( !m_wasStarted )
        {
            LOG_CHANNEL( "MANUAL_TIMER", "Warning! Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        m_lastRelativeTick = m_currentRelativeTick;
        m_currentRelativeTick += static_cast<uint64_t>( dt * 1000000.f );

        return true;
    }

} // namespace chestnut
