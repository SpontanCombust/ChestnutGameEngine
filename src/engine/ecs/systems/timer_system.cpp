#include "timer_system.hpp"

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

            for( auto timerIt = timerComp->timerList.begin(); timerIt != timerComp->timerList.end(); ++timerIt )
            {
                CLockedTimer *timer = *timerIt;

                // if the timer is null, erase it outright
                if( !timer )
                {
                    timerIt = timerComp->timerList.erase( timerIt );
                    continue;
                }

                if( timer->update() )
                {
                    STimerEvent *event = new STimerEvent();
                    event->timerID = timer->getID();
                    event->timerTimeInSeconds = timer->getCurrentTimeInSeconds();
                    event->timerIntervalInSeconds = timer->getUpdateIntervalInSeconds();
                    event->isTimerRepeating = timer->getIsRepeating();
                    m_localEventQueue.push( event );

                    if( !timer->getIsRepeating() && m_shouldDeleteNonRepeatingTimers )
                    {
                        timerIt = timerComp->timerList.erase( timerIt );
                        delete timer;
                        timer = nullptr;
                    }
                }
            }
        }
    }

    timer_id_t CTimerSystem::getNewTimerID() 
    {
        return ++m_timerIDCounter;
    }

    void CTimerSystem::setShouldDeleteNonRepeatingTimers( bool shouldDeleteNonRepeatingTimers ) 
    {
        m_shouldDeleteNonRepeatingTimers = shouldDeleteNonRepeatingTimers;
    }

} // namespace chestnut
