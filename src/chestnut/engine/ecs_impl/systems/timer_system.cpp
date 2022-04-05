#include "timer_system.hpp"

#include "../../main/engine.hpp"
#include "../components/timer_component.hpp"
#include "../events/timer_event.hpp"

namespace chestnut::engine
{
    CTimerSystem::CTimerSystem( CEngine& engine ) : ISystem( engine )
    {
        m_timerQueryID = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature<CTimerComponent>(),
            ecs::makeEntitySignature()
        );
    }

    CTimerSystem::~CTimerSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_timerQueryID );
    }

    void CTimerSystem::update( float deltaTime ) 
    {
        const ecs::CEntityQuery* query = getEngine().getEntityWorld().queryEntities( m_timerQueryID );

        query->forEachEntityWith< CTimerComponent >(
            [deltaTime, this]( CTimerComponent& timerComp )
            {
                for( CLockedManualTimer& timer : timerComp.vTimers )
                {
                    if( timer.tick( deltaTime ) )
                    {
                        STimerEvent event;
                        event.timerID = timer.getID();
                        event.timerTimeInSeconds = timer.getElapsedTimeInSeconds();
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
            }
        );
    }

} // namespace chestnut::engine
