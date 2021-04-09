#include "timer_system.hpp"

#include "engine/globals.hpp"

#include <algorithm>

namespace chestnut
{

    void CTimerSystem::submitBatch( CComponentBatch *batch ) 
    {
        if( batch->getSignature().includes<STimerComponent>() )
        {
            m_batchesWithTimerComps.push_back( batch );
        }
    }

    void CTimerSystem::clearBatches() 
    {
        m_batchesWithTimerComps.clear();
    }

    void CTimerSystem::update( float deltaTime ) 
    {
        std::vector< STimerComponent * > vecTimerComps;
        for( CComponentBatch *batch : m_batchesWithTimerComps )
        {
            vecTimerComps = batch->getComponents<STimerComponent>();
            for( STimerComponent *timerComp : vecTimerComps )
            {     
                for( CLockedTimer& timer : timerComp->vTimers )
                {
                    if( timer.update() )
                    {
                        STimerEvent *event = new STimerEvent();
                        event->timerID = timer.getID();
                        event->timerTimeInSeconds = timer.getCurrentTimeInSeconds();
                        event->timerIntervalInSeconds = timer.getUpdateIntervalInSeconds();
                        event->isTimerRepeating = timer.getIsRepeating();
                        theEventManager.raiseEvent( event );

                        // if a timer is supposed to tick only once
                        if( !timer.getIsRepeating() )
                        {
                            timerComp->removeTimer( timer.getID() );
                        }
                    }
                }
            }
        }
    }

} // namespace chestnut
