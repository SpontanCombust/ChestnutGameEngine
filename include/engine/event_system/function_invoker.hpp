#ifndef __CHESTNUT_FUNCTION_INVOKER_H__
#define __CHESTNUT_FUNCTION_INVOKER_H__

#include "event_base.hpp"

#include <cstddef>

namespace chestnut
{
    class IFunctionInvoker
    {
    public:
        virtual void invoke( SEvent *event ) {}
        virtual ~IFunctionInvoker() {}
    };
    
    

    template< typename EventType >
    class CFunctionInvoker : public IFunctionInvoker
    {
    private:
        event_function ( *m_func )( const EventType* );

    public:
        void bind( event_function ( *func )( const EventType* ) );
        void invoke( SEvent *event ) override;
    };

    template< typename EventType >
    void CFunctionInvoker<EventType>::bind( event_function( *func )( const EventType* ) ) 
    {
        m_func = func;
    }
    
    template< typename EventType >
    void CFunctionInvoker<EventType>::invoke( SEvent *event ) 
    {
        ( *m_func )( dynamic_cast< EventType* >( event ) );
    }



    template< typename T, typename EventType >
    class CMemberFunctionInvoker : public IFunctionInvoker
    {
    private:
        T *m_objPtr;
        event_function ( T::*m_membFunc )( const EventType* );

    public:
        void bind( T *objPtr, event_function ( T::*membFunc )( const EventType* ) );
        void invoke( SEvent* event ) override;
    };

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::bind( T *objPtr, event_function ( T::*membFunc )( const EventType* ) )
    {
        m_objPtr = objPtr;
        m_membFunc = membFunc;
    }

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::invoke( SEvent* event )
    {
        ( m_objPtr->*m_membFunc )( dynamic_cast< EventType* >( event ) );
    }

} // namespace chestnut


#endif // __CHESTNUT_FUNCTION_INVOKER_H__