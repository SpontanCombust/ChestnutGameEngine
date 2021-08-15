#include "timer_system.hpp"

#include "../../event_system/events/timer_event.hpp"
#include "../../globals.hpp"

#include <algorithm>

namespace chestnut
{
    void CTimerSystem::initQueries()
    {
        m_timerQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTimerComponent>();
        };
    }

    void CTimerSystem::update( uint32_t deltaTime ) 
    {
        ecs::forEachEntityInQuery< CTimerComponent >( m_timerQuery,
        [deltaTime]( CTimerComponent& timerComp )
        {
            for( CLockedManualTimer& timer : timerComp.vTimers )
            {
                if( timer.tick( deltaTime ) )
                {
                    STimerEvent *event = theEventManager.raiseEvent<STimerEvent>();
                    event->timerID = timer.getID();
                    event->timerTimeInSeconds = timer.getCurrentTimeInSeconds();
                    event->timerIntervalInSeconds = timer.getUpdateIntervalInSeconds();
                    event->isTimerRepeating = timer.getIsRepeating();

                    // if a timer is supposed to tick only once
                    if( !timer.getIsRepeating() )
                    {
                        timerComp.removeTimer( timer.getID() );
                    }
                }
            }
        });
    }

} // namespace chestnut
