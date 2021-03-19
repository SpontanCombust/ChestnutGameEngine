#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "../component_system.hpp"
#include "../components/timer_component.hpp"
#include "engine/event_system/events/timer_event.hpp"

#include <queue>

namespace chestnut
{
    class CTimerSystem : public IComponentSystem
    {
    private:
        timerid_t m_timerIDCounter = 0;
        std::unordered_map< entityid_t, STimerComponent* > m_timerCompMap;

    public:
        bool needsAnyOfComponents( const std::list< std::type_index >& compTypeIndexes ) override;
        void fetchComponents( const CComponentDatabase& dbRef ) override;
        void update( float deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__