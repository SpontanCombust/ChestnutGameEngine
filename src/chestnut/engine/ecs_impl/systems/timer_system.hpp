#ifndef __CHESTNUT_ENGINE_TIMER_SYSTEM_H__
#define __CHESTNUT_ENGINE_TIMER_SYSTEM_H__

#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CTimerSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_timerQuery;

    public:
        CTimerSystem( CEngine& engine );

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_TIMER_SYSTEM_H__