#ifndef __CHESTNUT_FUNCTION_INVOKER_H__
#define __CHESTNUT_FUNCTION_INVOKER_H__

#include "event_base.hpp"
#include "engine/types.hpp"

namespace chestnut
{
    // An interface class meant to be derived from and house an event function pointer to be invoked at some point
    class IFunctionInvoker
    {
    protected:
        bool m_wasBound;

    public:
        IFunctionInvoker();
        virtual void invoke( SEvent *event ) = 0;
        virtual ~IFunctionInvoker() {}
    };


    // Class housing an event function pointer that will be invoked at some point
    template< typename EventType >
    class CFunctionInvoker : public IFunctionInvoker
    {
    private:
        event_function ( *m_func )( const EventType& );

    public:
        // Sets invoker's function pointer
        void bind( event_function ( *func )( const EventType& ) );
        // Invokes stored function pointer if it was bound
        void invoke( SEvent *event ) override;
    };

    template< typename EventType >
    void CFunctionInvoker<EventType>::bind( event_function( *func )( const EventType& ) ) 
    {
        m_wasBound = true;
        m_func = func;
    }
    
    template< typename EventType >
    void CFunctionInvoker<EventType>::invoke( SEvent *event ) 
    {
        if( m_wasBound )
        {
            ( *m_func )( *dynamic_cast< EventType* >( event ) );
        }
    }



    // Class housing an event member function pointer that will be invoked at some point
    template< typename T, typename EventType >
    class CMemberFunctionInvoker : public IFunctionInvoker
    {
    private:
        T *m_objPtr;
        event_function ( T::*m_membFunc )( const EventType& );

    public:
        // Sets invoker's member function pointer
        void bind( T *objPtr, event_function ( T::*membFunc )( const EventType& ) );
        // Invokes stored member function pointer if it was bound
        void invoke( SEvent* event ) override;
    };

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::bind( T *objPtr, event_function ( T::*membFunc )( const EventType& ) )
    {
        m_wasBound = true;
        m_objPtr = objPtr;
        m_membFunc = membFunc;
    }

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::invoke( SEvent* event )
    {
        if( m_wasBound )
        {
            ( m_objPtr->*m_membFunc )( *dynamic_cast< EventType* >( event ) );
        }
    }

} // namespace chestnut


#endif // __CHESTNUT_FUNCTION_INVOKER_H__