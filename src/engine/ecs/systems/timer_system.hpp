#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "../system_bases/updatable_system.hpp"
#include "../system_bases/component_fetching_system.hpp"
#include "../system_bases/event_raising_system.hpp"
#include "../components/timer_component.hpp"
#include "engine/event_system/events/timer_event.hpp"

#include <queue>

namespace chestnut
{
    class CTimerSystem : public IUpdatableSystem, public IComponentFetchingSystem, public CEventRaisingSystem
    {
    private:
        timer_id_t m_timerIDCounter = 0;
        std::unordered_map< guid_t, STimerComponent* > m_timerCompMap;
        bool m_shouldDeleteNonRepeatingTimers = true;

    public:
        bool needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) override;
        void fetchComponents( const CComponentDatabase& dbRef ) override;
        void update( float deltaTime ) override;
        
        timer_id_t getNewTimerID();

        void setShouldDeleteNonRepeatingTimers( bool shouldDeleteNonRepeatingTimers );
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__