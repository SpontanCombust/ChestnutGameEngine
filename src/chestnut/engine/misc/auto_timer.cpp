#include "auto_timer.hpp"

#include "../debug/debug.hpp"

#include <chrono>

namespace chestnut
{
    CAutoTimer::CAutoTimer( timerid_t id ) 
    : ITimer( id )
    {
        m_startAbsoluteTick = 0;
    }

    uint64_t CAutoTimer::getAbsoluteTimeInMicroseconds() const
    {
        return static_cast<uint64_t>( std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::steady_clock::now().time_since_epoch() ).count() );
    }

    void CAutoTimer::reset()
    {
        m_startAbsoluteTick = getAbsoluteTimeInMicroseconds();
        m_currentRelativeTick = m_lastRelativeTick = 0;
    }

    bool CAutoTimer::tick() 
    {
        uint64_t measure = getAbsoluteTimeInMicroseconds();

        if( !m_wasStarted )
        {
            LOG_CHANNEL( "AUTO_TIMER", "Warning! Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        m_lastRelativeTick = m_currentRelativeTick;
        m_currentRelativeTick = measure - m_startAbsoluteTick;
        return true;
    }

} // namespace chestnut
