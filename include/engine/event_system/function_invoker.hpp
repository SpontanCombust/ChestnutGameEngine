#ifndef __CHESTNUT_FUNCTION_INVOKER_H__
#define __CHESTNUT_FUNCTION_INVOKER_H__

#include "event_base.hpp"

namespace chestnut
{
    class IFunctionInvoker
    {
    public:
        void invoke( SEvent *event )
        {
            invoke_internal( event );
        }

        virtual ~IFunctionInvoker() {}

    protected:
        virtual void invoke_internal( SEvent *event ) = 0;
    };
    
    

    template< typename EventType >
    class CFunctionInvoker : IFunctionInvoker
    {
    private:
        event_function ( *m_func )( EventType* );

    public:
        void bind( event_function ( *func )( EventType* ) );
        void invoke_internal( SEvent *event ) override;
    };

    template< typename EventType >
    void CFunctionInvoker<EventType>::bind( event_function( *func )( EventType* ) ) 
    {
        m_func = func;
    }
    
    template< typename EventType >
    void CFunctionInvoker<EventType>::invoke_internal( SEvent *event ) 
    {
        ( *m_func )( dynamic_cast< EventType* >( event ) );
    }
    


    template< typename T, typename EventType >
    class CMemberFunctionInvoker : IFunctionInvoker
    {
    private:
        T *m_objPtr;
        event_function ( T::*m_membFunc )( EventType* );

    public:
        void bind( T *objPtr, event_function ( T::*membFunc )( EventType* ) );
        void invoke_internal( SEvent* event ) override;
    };

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::bind( T *objPtr, event_function ( T::*membFunc )( EventType* ) )
    {
        m_objPtr = objPtr;
        m_membFunc = membFunc;
    }

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::invoke_internal( SEvent* event )
    {
        ( m_objPtr->*m_membFunc )( dynamic_cast< EventType* >( event ) );
    }

} // namespace chestnut


#endif // __CHESTNUT_FUNCTION_INVOKER_H__