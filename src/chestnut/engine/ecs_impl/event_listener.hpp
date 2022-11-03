#ifndef __CHESTNUT_ENGINE_EVENT_LISTENER_H__
#define __CHESTNUT_ENGINE_EVENT_LISTENER_H__

#include "chestnut/engine/macros.hpp"
#include "../types.hpp"

#include <typeindex>
#include <functional>

namespace chestnut::engine
{
	class CHESTNUT_API IEventListener
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
		std::function< event_function ( const EventType& ) > m_handler;
		std::function< bool ( const EventType& ) > m_filter;

    public:
		CEventListener();
		CEventListener( std::function< event_function( const EventType& ) > handler );
		CEventListener( std::function< event_function( const EventType& ) > handler, std::function< bool( const EventType& ) > filter );


		void setHandler( std::function< event_function( const EventType& ) > handler );

		template< typename T >
		void setHandler( event_function ( T::*handler )( const EventType& ), T *obj );


		void setFilter( std::function< bool ( const EventType& ) > filter );

		void invokeHandler( const EventType& event );

		bool testFilter( const EventType& event );

		void invokeHandlerIfFilterAccepts( const EventType& event );
    };

} // namespace chestnut::engine


#include "event_listener.tpp"


#endif // __CHESTNUT_ENGINE_EVENT_LISTENER_H__