#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "function_invoker.hpp"
#include "engine/debug/debug.hpp"

#include <typeindex>
#include <unordered_map>
#include <queue>
#include <vector>

namespace chestnut
{
    class CEventManager
    {
    protected:
        std::unordered_map< std::type_index, std::vector< IFunctionInvoker* >* > m_listenersMap;
        std::queue< SEvent* > m_eventQueue;

    public:
        template< typename EventType >
        void registerListener( event_function ( *func )( EventType* ) );

        template< typename T, typename EventType >
        void registerListener( T *objPtr, event_function ( T::*membFunc )( EventType* ) );

        void raiseEvent( SEvent *event );

        void clearListeners();

        void update( float deltaTime );

    private:
        void clearEventQueue();
        bool delegateEvent( SEvent *event );
        void delegateEvents();
    };

    template< typename EventType >
    void CEventManager::registerListener( event_function( *func )( EventType* ) ) 
    {
        if( !func )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null function ptr!" );
            return;
        }

        std::vector< IFunctionInvoker* > *typedListeners;
        typedListeners = m_listenersMap[ std::type_index( typeid( EventType ) ) ];
        if( !typedListeners )
        {
            typedListeners = new std::vector< IFunctionInvoker* >;
            m_listenersMap[ std::type_index( typeid( EventType ) ) ] = typedListeners;
        }

        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();
        invoker->bind( func );

        typedListeners->push_back( invoker );
    }
    
    template< typename T, typename EventType >
    void CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( EventType* ) ) 
    {
        if( !objPtr || !membFunc )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null object or member function ptr!" );
            return;
        }

        std::vector< IFunctionInvoker* > *typedListeners;
        typedListeners = m_listenersMap[ std::type_index( typeid( EventType ) ) ];
        if( !typedListeners )
        {
            typedListeners = new std::vector< IFunctionInvoker* >;
            m_listenersMap[ std::type_index( typeid( EventType ) ) ] = typedListeners;
        }

        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();
        invoker->bind( objPtr, membFunc );

        typedListeners->push_back( invoker );
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_MANAGER_H__