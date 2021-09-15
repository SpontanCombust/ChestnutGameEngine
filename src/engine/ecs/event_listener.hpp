#ifndef __CHESTNUT_EVENT_LISTENER_H__
#define __CHESTNUT_EVENT_LISTENER_H__

#include "../types.hpp"

#include <typeindex>
#include <functional>

namespace chestnut
{
	class IEventListener
	{
	public:
		std::type_index m_eventType = typeid(void);

	protected:
		bool m_isEnabled;


	public:
		void setEnabled( bool enable );
		bool isEnabled() const;

		virtual ~IEventListener() = default;
	};

    template< typename EventType >
    class CEventListener : public IEventListener
    { 
	protected:
		std::function< event_function ( const EventType& ) > m_consumer;
		std::function< bool ( const EventType& ) > m_filter;

    public:
		CEventListener();
		CEventListener( std::function< event_function( const EventType& ) > consumer );
		CEventListener( std::function< event_function( const EventType& ) > consumer, std::function< bool( const EventType& ) > filter );


		void setConsumer( std::function< event_function( const EventType& ) > consumer );

		// void setConsumer( event_function ( *consumer )( const EventType& ) );

		template< typename T >
		void setConsumer( event_function ( T::*consumer )( const EventType& ), T *obj );


		void setFilter( std::function< bool ( const EventType& ) > filter );

		void invokeConsumer( const EventType& event );

		bool testFilter( const EventType& event );

		void invokeConsumerIfFilterAccepts( const EventType& event );
    };

} // namespace chestnut


#include "event_listener.tpp"


#endif // __CHESTNUT_EVENT_LISTENER_H__