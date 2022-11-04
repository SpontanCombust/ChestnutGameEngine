#pragma once


#include "chestnut/engine/macros.hpp"
#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CTimerSystem : public ISystem
    {
    private:
        ecs::CEntityQuery *m_timerQuery;

    public:
        CTimerSystem( CEngine& engine );
        ~CTimerSystem();

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

