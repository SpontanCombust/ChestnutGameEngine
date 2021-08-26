#ifndef __CHESTNUT_EVENT_LISTENER_H__
#define __CHESTNUT_EVENT_LISTENER_H__

#include "event_base.hpp"
#include "../misc/exception.hpp"
#include "../misc/tindex.hpp"
#include "../types.hpp"

#include <functional>

namespace chestnut
{
	class IEventListener
	{
	public:
		eventtindex_t eventTindex;

		IEventListener();

		virtual void invoke( SEvent *event ) = 0;
		virtual bool checkConstraint( SEvent *event ) = 0;

		virtual ~IEventListener() = default;
	};

    template< typename EventType >
    class CEventListener : public IEventListener
    { 
	protected:
		std::function< event_function ( const EventType& ) > func;
		std::function< bool ( const EventType& ) > constraint;

    public:

		virtual void invoke( SEvent *event ) override;
		virtual bool checkConstraint( SEvent *event ) override;

        CEventListener();


		// Creates event listener of the event type specified in given function, return pointer to it
		template< typename E >
		friend CEventListener<E> *createEventListener( std::function< event_function ( const E& ) > func );

		/* Constrains event listener using constraintFunctor
			Throws an exception if constraintFunctor is incompatible with the listener */
		template< typename E >
		friend void constrainEventListener( CEventListener<E> *listener, std::function< bool( const E& ) > constraintFunctor );
    };

} // namespace chestnut


#include "event_listener.tpp"


#endif // __CHESTNUT_EVENT_LISTENER_H__