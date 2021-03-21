#ifndef __CHESTNUT_EVENT_CONSTRAINT_H__
#define __CHESTNUT_EVENT_CONSTRAINT_H__

#include "event_base.hpp"

#include <functional>

namespace chestnut
{
    // An interface class meant to be derived from and house a typed event verification functor
    class IEventConstraint
    {
    protected:
        bool m_wasSet;

    public:
        IEventConstraint();
        virtual bool verify( SEvent* ) = 0;
        virtual ~IEventConstraint() {}
        
    };


    // Class housing typed event verification functor
    template< typename EventType >
    class CEventConstraint : public IEventConstraint
    {
    private:
        std::function< bool( const EventType& ) > m_eventConstraintFunctor;

    public:
        // Sets the event verification functor
        void set( std::function< bool( const EventType& ) > eventConstraintFunctor );
        /* Uses the given event on the functor and returns whether it fits constraint functor's demands 
         * If the constraint has not been set yet returns true */
        bool verify( SEvent *event ) override;
    };

} // namespace chestnut


#include "event_constraint.tpp"


#endif // __CHESTNUT_EVENT_CONSTRAINT_H__