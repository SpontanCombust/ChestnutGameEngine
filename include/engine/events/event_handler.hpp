#ifndef __CHESTNUT_EVENT_HANDLER_H__
#define __CHESTNUT_EVENT_HANDLER_H__

#include "events.hpp"
#include "event_utils.hpp"
#include "engine/core/timer.hpp"

#include <unordered_map>
#include <vector>
#include <functional>

namespace chestnut
{
    class CEventHandler
    {
    private:
        std::unordered_map< std::string, std::vector< std::function< event_function() > > > m_genericEventListeners;
        std::unordered_map< std::string, std::vector< std::function< event_function( uint32_t, uint32_t ) > > > m_timerEventListeners;
        std::vector< CTimer > m_timers;

    public:
        template< class T >
        bool registerGenericListener( T *objPtr, event_function ( T::*objFunc )(), std::string eventName );

        bool registerGenericListener( event_function ( *func )(), std::string eventName );

        template< class T >
        bool registerTimerListener( T *objPtr, event_function ( T::*objFunc )( uint32_t deltaTime ), std::string eventName, uint32_t interval, bool isRepeating );

        bool registerTimerListener( event_function ( *func )( uint32_t deltaTime ), std::string eventName, uint32_t interval, bool isRepeating );
    };

    template< class T >
    bool CEventHandler::registerGenericListener( T *objPtr, event_function ( T::*objFunc )(), std::string eventName )
    {
        if( objPtr == nullptr || objFunc == nullptr )
            return false;

        m_genericEventListeners[ eventName ].push_back( std::bind( objFunc, objPtr ) );
        return true;
    }
    
    template< class T >
    bool CEventHandler::registerTimerListener( T *objPtr, event_function ( T::*objFunc )( uint32_t deltaTime ), std::string eventName, uint32_t interval, bool isRepeating ) 
    {
        if( objPtr == nullptr || objFunc == nullptr )
            return false;

        m_timerEventListeners[ eventName ].push_back( std::bind( objFunc, objPtr ) );
        m_timers.push_back( CTimer( interval, isRepeating ) );
        return true;
    }
    
} // namespace chestnut


#endif // __CHESTNUT_EVENT_HANDLER_H__