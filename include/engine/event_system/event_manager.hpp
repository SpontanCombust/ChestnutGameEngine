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
        // returns id of the listener
        template< typename EventType >
        size_t registerListener( event_function ( *func )( const EventType* ) );

        // returns id of the listener
        template< typename T, typename EventType >
        size_t registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType* ) );


        template< typename EventType >
        void unregisterListenerByID( size_t ID );


        void raiseEvent( SEvent *event );

        void clearListeners();

        void update( float deltaTime );

        ~CEventManager();

    private:
        void clearEventQueue();
        bool delegateEvent( SEvent *event );
        void delegateEvents();
    };

    template< typename EventType >
    size_t CEventManager::registerListener( event_function( *func )( const EventType* ) ) 
    {
        if( !func )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null function ptr!" );
            return 0;
        }

        std::vector< IFunctionInvoker* > *typedListeners;
        typedListeners = m_listenersMap[ std::type_index( typeid( EventType ) ) ];
        if( !typedListeners )
        {
            typedListeners = new std::vector< IFunctionInvoker* >;
            m_listenersMap[ std::type_index( typeid( EventType ) ) ] = typedListeners;
        }

        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();

        size_t id = (size_t)func;
        invoker->bind( func, id );

        typedListeners->push_back( invoker );

        return id;
    }
    

    template< typename T, typename EventType >
    size_t CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType* ) ) 
    {
        if( !objPtr || !membFunc )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null object or member function ptr!" );
            return 0;
        }

        std::vector< IFunctionInvoker* > *typedListeners;
        typedListeners = m_listenersMap[ std::type_index( typeid( EventType ) ) ];
        if( !typedListeners )
        {
            typedListeners = new std::vector< IFunctionInvoker* >;
            m_listenersMap[ std::type_index( typeid( EventType ) ) ] = typedListeners;
        }

        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();

        // This may produce collisions
        size_t id = (size_t)objPtr + (size_t)&membFunc; 
        invoker->bind( objPtr, membFunc, id );

        typedListeners->push_back( invoker );

        return id;
    }
    

    template< typename EventType >
    void CEventManager::unregisterListenerByID( size_t id ) 
    {
        std::vector< IFunctionInvoker* > *typedListeners;
        typedListeners = m_listenersMap[ std::type_index( typeid( EventType ) ) ];
        if( !typedListeners )
            return;

        for( auto it = typedListeners->begin(); it != typedListeners->end(); ++it )
        {
            if( (*it)->getID() == id )
            {
                typedListeners->erase( it );
                break;
            }
        }
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_MANAGER_H__