#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "../component_system.hpp"
#include "../components/timer_component.hpp"

namespace chestnut
{
    class CTimerSystem : public IComponentSystem
    {
    private:
        ecs::SEntityQuery m_timerQuery;

    public:
        void initQueries() override;

        void update( uint32_t deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__