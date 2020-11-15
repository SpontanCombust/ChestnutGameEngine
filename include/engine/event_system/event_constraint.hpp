#ifndef __CHESTNUT_EVENT_CONSTRAINT_H__
#define __CHESTNUT_EVENT_CONSTRAINT_H__

#include "event_base.hpp"

#include <functional>

namespace chestnut
{
    struct IEventConstraint
    {
        virtual bool verify( SEvent* ) { return false; }
        virtual ~IEventConstraint() {}
    };


    template< typename EventType >
    struct SEventConstraint : IEventConstraint
    {
        std::function< bool( const EventType* ) > eventVerificationFunctor;
        bool verify( SEvent *event ) override;
    };

    template< typename EventType >
    bool SEventConstraint<EventType>::verify( SEvent *event )
    {
        return eventVerificationFunctor( dynamic_cast<EventType*>( event ) );
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_CONSTRAINT_H__