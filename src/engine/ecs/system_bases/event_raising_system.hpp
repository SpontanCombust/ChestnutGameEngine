#ifndef __CHESTNUT_EVENT_RAISING_SYSTEM_H__
#define __CHESTNUT_EVENT_RAISING_SYSTEM_H__

#include "engine/event_system/event_manager.hpp"

#include <queue>
#include <functional>

namespace chestnut
{
    class CEventRaisingSystem
    {
    protected:
        std::queue< SEvent* > m_localEventQueue;

    public:
        virtual bool needsToRaiseEvents();
        virtual void raiseEvents( CEventManager& eventManagerRef );
        
        virtual ~CEventRaisingSystem() {}

    protected:
        template< typename EventType >
        void cancelEvents( std::function< bool ( const EventType& ) > cancelationRule );
    };



    template< typename EventType >
    void CEventRaisingSystem::cancelEvents( std::function< bool ( const EventType& ) > cancelationRule ) 
    {
        // Queue to push to only events that don't fit cancelation rule
        std::queue< SEvent* > filteredLocalEventQueue;

        SEvent *event;
        EventType *castedEvent;
        while( !m_localEventQueue.empty() )
        {
            event = m_localEventQueue.front();
            castedEvent = dynamic_cast< EventType* >( event );
            m_localEventQueue.pop();
            
            // If event's type is not the one specified for the function, automatically push it to the queue with filtered out events
            if( !castedEvent )
            {
                filteredLocalEventQueue.push( event );
            }
            // If event type matches, check the cancelation rule. If it's successful, get rid of the event.
            else if( cancelationRule( *castedEvent ) )
            {
                delete castedEvent;
            }
            // ... otherwise push the event to the queue with filtered out events
            else
            {
                filteredLocalEventQueue.push( castedEvent );
            }
        }

        // Copy-assign filtered events back to local event queue
        m_localEventQueue = filteredLocalEventQueue;
    }

} // namespace chestnut

#endif // __CHESTNUT_EVENT_RAISING_SYSTEM_H__