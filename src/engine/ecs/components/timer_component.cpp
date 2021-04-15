#include "timer_component.hpp"

namespace chestnut
{   
    timerid_t STimerComponent::m_timerIDAccumulator = 0;
    
    STimerComponent::~STimerComponent() 
    {
        vTimers.clear();
    }

    timerid_t STimerComponent::addTimer( float updateIntervalSec, bool isRepeating ) 
    {
        ++m_timerIDAccumulator;
        CLockedManualTimer timer = CLockedManualTimer( m_timerIDAccumulator, updateIntervalSec, isRepeating );
        timer.start();
        vTimers.push_back( timer );
        return m_timerIDAccumulator;
    }

    bool STimerComponent::removeTimer( timerid_t id ) 
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

    void STimerComponent::removeTimers() 
    {
        vTimers.clear();
    }

} // namespace chestnut
