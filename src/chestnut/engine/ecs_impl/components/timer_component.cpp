#include "chestnut/engine/ecs_impl/components/timer_component.hpp"

namespace chestnut::engine
{   
    timerid_t CTimerComponent::m_timerIDAccumulator = 0;
    
    CTimerComponent::~CTimerComponent() 
    {
        vTimers.clear();
    }

    timerid_t CTimerComponent::addTimer( float updateIntervalSec, bool isRepeating ) 
    {
        ++m_timerIDAccumulator;
        CLockedManualTimer timer = CLockedManualTimer( m_timerIDAccumulator, updateIntervalSec, isRepeating );
        timer.start();
        vTimers.push_back( timer );
        return m_timerIDAccumulator;
    }

    bool CTimerComponent::removeTimer( timerid_t id ) 
    {
        auto it = vTimers.begin();
        for(; it != vTimers.end(); ++it )
        {
            if( it->getID() == id )
            {
                vTimers.erase( it );
                return true;
            }
        }
        return false;
    }

    void CTimerComponent::removeTimers() 
    {
        vTimers.clear();
    }

} // namespace chestnut::engine
