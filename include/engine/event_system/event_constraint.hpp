#ifndef __CHESTNUT_EVENT_CONSTRAINT_H__
#define __CHESTNUT_EVENT_CONSTRAINT_H__

#include "event_base.hpp"

#include <functional>

namespace chestnut
{
    class IEventConstraint
    {
    public:
        virtual bool verify( SEvent* ) { return false; }
        virtual ~IEventConstraint() {}
    };


    template< typename EventType >
    class CEventConstraint : public IEventConstraint
    {
    private:
        std::function< bool( const EventType& ) > m_eventConstraintFunctor;

    public:
        void set( std::function< bool( const EventType& ) > eventConstraintFunctor );
        bool verify( SEvent *event ) override;
    };

    template< typename EventType >
    void CEventConstraint<EventType>::set( std::function< bool( const EventType& ) > eventConstraintFunctor ) 
    {
        m_eventConstraintFunctor = eventConstraintFunctor;
    }

    template< typename EventType >
    bool CEventConstraint<EventType>::verify( SEvent *event )
    {
        return m_eventConstraintFunctor( *dynamic_cast<EventType*>( event ) );
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_CONSTRAINT_H__