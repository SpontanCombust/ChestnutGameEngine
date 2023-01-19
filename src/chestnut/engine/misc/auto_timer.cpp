#include "chestnut/engine/misc/auto_timer.hpp"

#include "chestnut/engine/debug/log.hpp"

#include <chrono>

namespace chestnut::engine
{
    CAutoTimer::CAutoTimer( timerid_t id ) 
    : ITimer( id )
    {
        m_startAbsoluteTick = 0;
    }

    uint64_t CAutoTimer::getAbsoluteTimeInMicroseconds() const
    {
        return static_cast<uint64_t>( std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::high_resolution_clock::now().time_since_epoch() ).count() );
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
            LOG_WARNING( "Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        m_lastRelativeTick = m_currentRelativeTick;
        m_currentRelativeTick = measure - m_startAbsoluteTick;
        return true;
    }

} // namespace chestnut::engine
