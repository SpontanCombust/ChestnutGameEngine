#ifndef __CHESTNUT_TIMER_SYSTEM_H__
#define __CHESTNUT_TIMER_SYSTEM_H__

#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut
{
    class CTimerSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_timerQuery;

    public:
        CTimerSystem( CEngine& engine );

        void update( float deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_TIMER_SYSTEM_H__