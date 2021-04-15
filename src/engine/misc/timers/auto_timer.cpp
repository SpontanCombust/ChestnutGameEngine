#include "auto_timer.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    CAutoTimer::CAutoTimer( timerid_t id ) 
    : ITimer( id )
    {
        reset( true );
        m_wasStarted = false;
    }

    void CAutoTimer::reset( bool init )
    {
        if( !init )
        {
            m_startTick = SDL_GetTicks();
            m_currentRelativeTick = m_lastRelativeTick = 0;
        }
        m_tickCount = 0;
    }

    bool CAutoTimer::tick() 
    {
        if( !m_wasStarted )
        {
            LOG_CHANNEL( "AUTO_TIMER", "Warning! Trying to update a timer that wasn't started yet! ID: " << m_timerID );
            return false;
        }

        uint32_t currentRelativeTick = SDL_GetTicks() - m_startTick;

        if( currentRelativeTick > m_currentRelativeTick )
        {
            m_lastRelativeTick = m_currentRelativeTick;
            m_currentRelativeTick = currentRelativeTick;
            m_tickCount++;
            return true;
        }

        return false;
    }

} // namespace chestnut
