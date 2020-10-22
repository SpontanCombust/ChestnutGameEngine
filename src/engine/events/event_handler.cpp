#include "engine/events/event_handler.hpp"

namespace chestnut
{
    bool CEventHandler::registerGenericListener( event_function ( *func )(), std::string eventName )
    {
        if( func == nullptr )
            return false;

        m_genericEventListeners[ eventName ].push_back( std::bind( func ) );
        return true;
    }
    
    bool CEventHandler::registerTimerListener( event_function ( *func )( uint32_t deltaTime ), std::string eventName, uint32_t interval, bool isRepeating ) 
    {
        if( func == nullptr )
            return false;

        m_timerEventListeners[ eventName ].push_back( std::bind( func, std::placeholders::_1 ) );
        m_timers.push_back( CTimer( interval, isRepeating ) );
        return true;
    }

} // namespace chestnut
