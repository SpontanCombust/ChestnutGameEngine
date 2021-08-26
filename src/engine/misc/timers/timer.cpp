#include "timer.hpp"

#include "../../debug/debug.hpp"

namespace chestnut
{
    ITimer::ITimer( timerid_t id )
    {
        m_timerID = id;
    }

    timerid_t ITimer::getID()
    {
        return m_timerID;
    }

    void ITimer::start() 
    {
        if( !m_wasStarted )
        {
            reset( false );
        }
        m_wasStarted = true;
    }

    void ITimer::resetAndStart() 
    {
        reset( false );
        start();
    }

    uint32_t ITimer::getCurrentTimeInMiliseconds() 
    {
        return m_currentRelativeTick;
    }

    float ITimer::getCurrentTimeInSeconds() 
    {
        return (float)m_currentRelativeTick / 1000.f;
    }

    uint32_t ITimer::getDeltaTime() 
    {
        uint32_t dt = m_currentRelativeTick - m_lastRelativeTick;

        return dt;
    }

    float ITimer::getAvgUpdatesPerSec() 
    {
        if( m_currentRelativeTick > 0 )
            return (float)m_tickCount / (float)m_currentRelativeTick * 1000.f;
        return 0;
    }

} // namespace chestnut
