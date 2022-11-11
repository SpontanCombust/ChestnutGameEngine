#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/ecs_impl/logic_system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CKinematics2DSystem : public ILogicSystem
    {
    private:
        ecs::CEntityQuery *m_kinematicQuery;
        
    public:
        CKinematics2DSystem() = default;
        CKinematics2DSystem(systempriority_t priority);
        ~CKinematics2DSystem();

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

