#ifndef __CHESTNUT_EVENT_LISTENER_H__
#define __CHESTNUT_EVENT_LISTENER_H__

#include "function_invoker.hpp"
#include "event_constraint.hpp"
#include "engine/misc/exception.hpp"
#include "engine/misc/tindex.hpp"

#include <typeindex>

namespace chestnut
{
    // Struct containing function invoker and its (optional) constraint
    struct SEventListener 
    { 
        std::type_index eventTindex;
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




    template< typename EventType >
    SEventListener createEventListener( event_function ( *func )( const EventType& ) )
    {
        SEventListener listener;

        // assign type index to maintain coherence when setting constraint
        listener.eventTindex = TINDEX( EventType );

        // Creates function invoker based on function in the parameter
        CFunctionInvoker<EventType> *invoker = new CFunctionInvoker<EventType>();
        invoker->bind( func );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        return listener;
    }

    template< typename T, typename EventType >
    SEventListener createEventListener( T *objPtr, event_function ( T::*membFunc )( const EventType& ) )
    {
        if( !objPtr )
        {
            throw ChestnutException( "Can't create an event listener for a null object!" );
        }

        SEventListener listener;

        // assign type index to maintain coherence when setting constraint
        listener.eventTindex = TINDEX( EventType );

        // Creates member function invoker based on function in the parameter
        CMemberFunctionInvoker<T, EventType> *invoker = new CMemberFunctionInvoker<T, EventType>();
        invoker->bind( objPtr, membFunc );

        // Gives listener a function invoker
        listener.functionInvoker = invoker;

        return listener;  
    }

    template< typename EventType >
    void constrainEventListener( SEventListener& listener, std::function< bool( const EventType& ) > constraintFunctor )
    {
        // Checks if the given constraint functor is for the same event type as the function invoker
        if( !listener.functionInvoker || listener.eventTindex != TINDEX( EventType ) )
        {
            throw ChestnutException( "Can't constrain event listener with incompatible constraint functor!" );
        }

        // Retrieve the constraint
        CEventConstraint<EventType> *constraint;

        // If constraint has been set earlier, retrieve it
        if( listener.constraint )
        {
            constraint = dynamic_cast< CEventConstraint<EventType>* >( listener.constraint );
        }
        // ...if not, create a new one
        else
        {
            constraint = new CEventConstraint<EventType>();
        }

        // Set the functor for the constraint
        constraint->set( constraintFunctor );

        // assign new constraint
        listener.constraint = constraint;
    }

} // namespace chestnut


#endif // __CHESTNUT_EVENT_LISTENER_H__