#pragma once


#include "chestnut/engine/macros.hpp"
#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CHESTNUT_API CKinematics2DSystem : public ISystem
    {
    private:
        ecs::CEntityQuery *m_kinematicQuery;
        
    public:
        CKinematics2DSystem( CEngine& engine );
        ~CKinematics2DSystem();

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

