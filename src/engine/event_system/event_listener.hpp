#ifndef __CHESTNUT_EVENT_LISTENER_H__
#define __CHESTNUT_EVENT_LISTENER_H__

#include "function_invoker.hpp"
#include "event_constraint.hpp"
#include "engine/misc/exception.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

namespace chestnut
{
    // Struct containing function invoker and its (optional) constraint
    struct SEventListener 
    { 
        eventtindex_t eventTindex;
        IFunctionInvoker *functionInvoker;
        IEventConstraint *constraint;

        SEventListener& operator=( const SEventListener& other );

        SEventListener();
    };

    // Creates event listener of the event type specified in given function
    template< typename EventType >
    SEventListener createEventListener( event_function ( *func )( const EventType& ) );

    /* Creates event listener of the event type specified in given object and member function
       Throws an exception if objPtr is null */
    template< typename T, typename EventType >
    SEventListener createEventListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) );

    /* Constrains event listener using constraintFunctor
       Throws an exception if constraintFunctor is incompatible with the listener */
    template< typename EventType >
    void constrainEventListener( SEventListener& listener, std::function< bool( const EventType& ) > constraintFunctor );

    /* Frees memory from listener's members
       It's mandatory to use this function or free memory from members manually, as the destructor WON'T do it by itself */
    void destroyEventListener( SEventListener& listener );

} // namespace chestnut


#include "event_listener.tpp"


#endif // __CHESTNUT_EVENT_LISTENER_H__