#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "component_system.hpp"
#include "../components/timer_component.hpp"
#include "engine/event_system/events/timer_event.hpp"

#include <queue>

namespace chestnut
{
    class CTimerSystem : public IComponentSystem
    {
    private:
        timerid_t m_timerIDCounter = 0;
        std::vector< CComponentBatch * > m_batchesWithTimerComps;

    public:
        void submitBatch( CComponentBatch *batch ) override;
        void clearBatches() override;
        void update( float deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__