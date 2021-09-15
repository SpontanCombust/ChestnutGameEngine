#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "../system.hpp"
#include "../components/timer_component.hpp"

namespace chestnut
{
    class CTimerSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_timerQuery;

    public:
        CTimerSystem( CEngine& engine );

        void update( uint32_t deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__