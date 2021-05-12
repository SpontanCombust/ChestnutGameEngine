#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "component_system.hpp"
#include "../components/timer_component.hpp"
#include "engine/event_system/events/timer_event.hpp"

namespace chestnut
{
    class CTimerSystem : public IComponentSystem
    {
    private:
        std::vector<STimerComponent *> m_vecTimerComps;

    public:
        void submitComponents( CComponentBatch *batch ) override;
        void clearComponents() override;
        void update( uint32_t deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__