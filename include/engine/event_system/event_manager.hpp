#ifndef __CHESTNUT_EVENT_MANAGER_H__
#define __CHESTNUT_EVENT_MANAGER_H__

#include "function_invoker.hpp"
#include "event_constraint.hpp"
#include "engine/debug/debug.hpp"

#include <list>
#include <typeindex>
#include <unordered_map>
#include <queue>

namespace chestnut
{
    struct SEventListener 
    { 
        IFunctionInvoker *functionInvoker;
        IEventConstraint *constraint;
    };

    class CEventManager
    {
    private:
        int m_idCounter = 0;

        std::unordered_map< std::type_index, std::list< int > > m_eventTypeToIDListMap;
        std::unordered_map< int, SEventListener > m_IDToListenerMap;
        std::queue< SEvent* > m_eventQueue;

    public:
        // returns id of the listener
        template< typename EventType >
        int registerListener( event_function ( *func )( const EventType* ) );

        // returns id of the listener
        template< typename T, typename EventType >
        int registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType* ) );


        template< typename EventType >
        void unregisterListenerByID( int ID );


        template< typename EventType >
        void constrainListenerByID( int id, std::function< bool( const EventType* ) > constraintFunctor );


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
    int CEventManager::registerListener( event_function( *func )( const EventType* ) ) 
    {
        if( !func )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null function ptr!" );
            return 0;
        }

        m_idCounter++;

        SEventListener &listener = m_IDToListenerMap[ m_idCounter ];

        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();
        invoker->bind( func );

        listener.functionInvoker = invoker;

        m_eventTypeToIDListMap[ std::type_index( typeid( EventType ) ) ].push_back( m_idCounter );
        
        return m_idCounter;
    }
    

    template< typename T, typename EventType >
    int CEventManager::registerListener( T *objPtr, event_function ( T::*membFunc )( const EventType* ) ) 
    {
        if( !objPtr || !membFunc )
        {
            LOG_CHANNEL( "EVENT_MANAGER", "Attempt to register a null object or member function ptr!" );
            return 0;
        }

        m_idCounter++;

        SEventListener &listener = m_IDToListenerMap[ m_idCounter ];
        
        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();
        invoker->bind( objPtr, membFunc );

        listener.functionInvoker = invoker;

        m_eventTypeToIDListMap[ std::type_index( typeid( EventType ) ) ].push_back( m_idCounter );

        return m_idCounter;
    }
    

    template< typename EventType >
    void CEventManager::unregisterListenerByID( int id ) 
    {
        // if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
            return;

        SEventListener &listener = m_IDToListenerMap[ id ];

        delete listener.functionInvoker;
        listener.functionInvoker = nullptr;

        if( listener.constraint )
        {
            delete listener.constraint;
            listener.constraint = nullptr;
        }

        m_IDToListenerMap.erase( id );


        std::list< int > &typedIDList = m_eventTypeToIDListMap[ std::type_index( typeid( EventType ) ) ];

        for( auto it = typedIDList.begin(); it != typedIDList.end(); ++it )
        {
            if( *it == id )
            {
                typedIDList.erase( it );
                break;
            }
        }
    }


    template< typename EventType >
    void CEventManager::constrainListenerByID( int id, std::function< bool( const EventType* ) > constraintFunctor )
    {
        // if listener even exists
        if( m_IDToListenerMap.find( id ) == m_IDToListenerMap.end() )
            return;

        if( m_IDToListenerMap[ id ].constraint )
            delete ( m_IDToListenerMap[ id ].constraint );

        SEventConstraint<EventType> *constraint = new SEventConstraint<EventType>();
        constraint->eventVerificationFunctor = constraintFunctor;

        m_IDToListenerMap[ id ].constraint = constraint;
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_MANAGER_H__