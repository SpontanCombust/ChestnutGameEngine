#include "timer_system.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/components/timer_component.hpp"
#include "chestnut/engine/ecs_impl/events/timer_event.hpp"

namespace chestnut::engine
{
    CTimerSystem::CTimerSystem(systempriority_t priority) 
    : ILogicSystem(priority)
    {
        m_timerQuery = CEngine::getInstance().getEntityWorld().createQuery(
            ecs::makeEntitySignature<CTimerComponent>()
        );
    }

    CTimerSystem::~CTimerSystem() 
    {
        CEngine::getInstance().getEntityWorld().destroyQuery( m_timerQuery );
    }

    void CTimerSystem::update( float deltaTime ) 
    {
        CEngine::getInstance().getEntityWorld().queryEntities( m_timerQuery );

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
                        CEngine::getInstance().getEventManager().raiseEvent( event );

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
