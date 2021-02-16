#include "event_listener.hpp"

namespace chestnut
{
    SEventListener::SEventListener() 
    : eventTindex( TINDEX( void ) )
    {
        functionInvoker = nullptr;
        constraint = nullptr;
    }

    SEventListener& SEventListener::operator=( const SEventListener& other ) 
    {
        eventTindex = other.eventTindex;
        functionInvoker = other.functionInvoker;
        constraint = other.constraint;
        return *this;
    }

    void destroyEventListener( SEventListener& listener ) 
    {
        if( listener.functionInvoker )
        {
            delete listener.functionInvoker;
            listener.functionInvoker = nullptr;
        }

        if( listener.constraint )
        {
            delete listener.constraint;
            listener.constraint = nullptr;
        }
    }

} // namespace chestnut

