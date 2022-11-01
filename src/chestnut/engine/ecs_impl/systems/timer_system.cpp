#include "timer_system.hpp"

#include "../../main/engine.hpp"
#include "../components/timer_component.hpp"
#include "../events/timer_event.hpp"

namespace chestnut::engine
{
    CTimerSystem::CTimerSystem( CEngine& engine ) : ISystem( engine )
    {
        m_timerQuery = getEngine().getEntityWorld().createQuery(
            ecs::makeEntitySignature<CTimerComponent>()
        );
    }

    CTimerSystem::~CTimerSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_timerQuery );
    }

    void CTimerSystem::update( float deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_timerQuery );

        m_timerQuery->forEach(std::function(
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
        ));
    }

} // namespace chestnut::engine
