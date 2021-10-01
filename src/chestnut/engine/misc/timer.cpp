#include "timer.hpp"

namespace chestnut::engine
{
    ITimer::ITimer( timerid_t id )
    {
        m_timerID = id;

        m_currentRelativeTick = 0;
        m_lastRelativeTick = 0;

        m_wasStarted = false;
    }

    timerid_t ITimer::getID()
    {
        return m_timerID;
    }

    void ITimer::start() 
    {
        m_wasStarted = true;
        reset();
    }

    uint64_t ITimer::getElapsedTimeInMicroseconds() 
    {
        return m_currentRelativeTick;
    }

    uint64_t ITimer::getElapsedTimeInMiliseconds() 
    {
        return m_currentRelativeTick / 1000;
    }

    double ITimer::getElapsedTimeInSeconds() 
    {
        return static_cast<double>( m_currentRelativeTick ) / 1000000.0;
    }

    float ITimer::getDeltaTime() 
    {
        return static_cast<float>( m_currentRelativeTick - m_lastRelativeTick ) / 1000000.f;
    }

    float ITimer::getUpdatesPerSec() 
    {
        if( m_currentRelativeTick > 0)
        {
            return 1000000.f / static_cast<float>( m_currentRelativeTick - m_lastRelativeTick );
        }

        return 0.f;
    }

} // namespace chestnut::engine
