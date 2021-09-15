#include "timer_system.hpp"

#include "../events/timer_event.hpp"

namespace chestnut
{
    CTimerSystem::CTimerSystem( CEngine& engine ) : ISystem( engine )
    {
        m_timerQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTimerComponent>();
        };
    }

    void CTimerSystem::update( uint32_t deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_timerQuery );

        ecs::forEachEntityInQuery< CTimerComponent >( m_timerQuery,
        [deltaTime, this]( CTimerComponent& timerComp )
        {
            for( CLockedManualTimer& timer : timerComp.vTimers )
            {
                if( timer.tick( deltaTime ) )
                {
                    STimerEvent event;
                    event.timerID = timer.getID();
                    event.timerTimeInSeconds = timer.getCurrentTimeInSeconds();
                    event.timerIntervalInSeconds = timer.getUpdateIntervalInSeconds();
                    event.isTimerRepeating = timer.getIsRepeating();
                    getEngine().getEventManager().raiseEvent( event );

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
