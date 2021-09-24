#ifndef __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__
#define __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__

#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut
{
    class CKinematics2DSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_transformKinematicQuery;
        
    public:
        CKinematics2DSystem( CEngine& engine );

        void update( float deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__