#include "timer_system.hpp"

#include "engine/globals.hpp"

#include <algorithm>

namespace chestnut
{

    void CTimerSystem::submitComponents( CComponentBatch *batch ) 
    {
        if( batch->getSignature().includes<STimerComponent>() )
        {
            batch->getComponentsAppendToVec( m_vecTimerComps );
        }
    }

    void CTimerSystem::clearComponents() 
    {
        m_vecTimerComps.clear();
    }

    void CTimerSystem::update( uint32_t deltaTime ) 
    {
        for( STimerComponent *timerComp : m_vecTimerComps )
        {     
            for( CLockedManualTimer& timer : timerComp->vTimers )
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
                        timerComp->removeTimer( timer.getID() );
                    }
                }
            }
        }
    }

} // namespace chestnut
