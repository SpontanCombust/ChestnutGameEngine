#include "chestnut/engine/misc/manual_timer.hpp"

#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
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
            LOG_WARNING( "Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        m_lastRelativeTick = m_currentRelativeTick;
        m_currentRelativeTick += static_cast<uint64_t>( dt * 1000000.f );

        return true;
    }

} // namespace chestnut::engine
