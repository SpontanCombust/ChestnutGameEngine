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

    void CTimerSystem::update( uint32_t deltaTime ) 
    {
        std::vector< STimerComponent * > vecTimerComps;
        for( CComponentBatch *batch : m_batchesWithTimerComps )
        {
            vecTimerComps = batch->getComponents<STimerComponent>();
            for( STimerComponent *timerComp : vecTimerComps )
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
    }

} // namespace chestnut
