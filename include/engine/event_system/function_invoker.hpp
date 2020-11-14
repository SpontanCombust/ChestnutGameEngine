#ifndef __CHESTNUT_FUNCTION_INVOKER_H__
#define __CHESTNUT_FUNCTION_INVOKER_H__

#include "event_base.hpp"

namespace chestnut
{
    class IFunctionInvoker
    {
    protected:
        size_t m_ID;

    public:
        size_t getID() { return m_ID; }

        virtual void invoke( SEvent *event ) {}
        virtual ~IFunctionInvoker() {}
    };
    
    

    template< typename EventType >
    class CFunctionInvoker : public IFunctionInvoker
    {
    private:
        event_function ( *m_func )( const EventType* );

    public:
        void bind( event_function ( *func )( const EventType* ), size_t id );
        void invoke( SEvent *event ) override;
    };

    template< typename EventType >
    void CFunctionInvoker<EventType>::bind( event_function( *func )( const EventType* ), size_t id ) 
    {
        m_func = func;
        m_ID = id;
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
        void bind( T *objPtr, event_function ( T::*membFunc )( const EventType* ), size_t id );
        void invoke( SEvent* event ) override;
    };

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::bind( T *objPtr, event_function ( T::*membFunc )( const EventType* ), size_t id )
    {
        m_objPtr = objPtr;
        m_membFunc = membFunc;
        m_ID = id;
    }

    template< typename T, typename EventType >
    void CMemberFunctionInvoker<T,EventType>::invoke( SEvent* event )
    {
        ( m_objPtr->*m_membFunc )( dynamic_cast< EventType* >( event ) );
    }

} // namespace chestnut


#endif // __CHESTNUT_FUNCTION_INVOKER_H__