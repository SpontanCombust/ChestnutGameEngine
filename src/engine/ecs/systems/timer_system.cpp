#include "timer_system.hpp"

#include "engine/globals.hpp"

#include <algorithm>

namespace chestnut
{
    bool CTimerSystem::needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) 
    {
        return std::any_of( compTypeIndexes.begin(), compTypeIndexes.end(),
            []( std::type_index tindex ) -> bool
            {
                return tindex == TINDEX( STimerComponent );
            }
        );
    }

    void CTimerSystem::fetchComponents( const CComponentDatabase& dbRef ) 
    {
        m_timerCompMap = dbRef.getComponentMapOfType< STimerComponent >();
    }

    void CTimerSystem::update( float deltaTime ) 
    {
        STimerComponent *timerComp;
        for( auto& pair : m_timerCompMap )
        {
            timerComp = pair.second;

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

} // namespace chestnut
