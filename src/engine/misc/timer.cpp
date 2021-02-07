#include "engine/misc/timer.hpp"

namespace chestnut
{
    CTimer::CTimer( int id )
    : m_timerID(id)
    {
        reset( true );
        m_wasStarted = false;
    }

    int CTimer::getID()
    {
        return m_timerID;
    }

    void CTimer::reset( bool init )
    {
        if( !init )
        {
            m_startTick = SDL_GetTicks();
            m_currentTick = m_lastTick = m_startTick;
        }
        m_updateCount = 0;
        m_lastPauseTick = 0;
        m_pausedTicks = 0;

        m_isPaused = false;
    }

    void CTimer::start()
    {
        if( !m_wasStarted )
        {
            m_startTick = SDL_GetTicks();
            m_currentTick = m_lastTick = m_startTick;
            m_wasStarted = true;
        }
    }

    void CTimer::pause() 
    {
        m_isPaused = true;
        m_lastPauseTick = SDL_GetTicks();
    }

    void CTimer::unpause() 
    {
        m_isPaused = false;
        m_pausedTicks += SDL_GetTicks() - m_lastPauseTick;
    }

    bool CTimer::isPaused() 
    {
        return m_isPaused;
    }

    uint32_t CTimer::getCurrentTimeInMiliseconds() 
    {
        return m_currentTick;
    }

    float CTimer::getCurrentTimeInSeconds() 
    {
        return (float)m_currentTick / 1000.f;
    }

    float CTimer::getDeltaTime() 
    {
        uint32_t dt = m_currentTick - m_lastTick;

        if( dt == 0 )
        {
            return 0.000f;
        }

        return (float)dt / 1000.f;
    }

    float CTimer::getAvgUpdatesPerSec() 
    {
        if( m_currentTick > 0 )
            return (float)m_updateCount / (float)m_currentTick * 1000.f;
        return 0;
    }

    bool CTimer::update( bool shouldStartIfDidntAlready ) 
    {
        if( shouldStartIfDidntAlready )
        {
            start();
        }

        if( m_wasStarted && !m_isPaused )
        {
            m_lastTick = m_currentTick;
            m_currentTick = SDL_GetTicks() - m_startTick - m_pausedTicks;
            m_updateCount++;
            return true;
        }
        
        return false;
    }

} // namespace chestnut
