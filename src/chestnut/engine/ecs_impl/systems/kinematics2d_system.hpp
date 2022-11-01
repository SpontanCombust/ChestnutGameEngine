#ifndef __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__
#define __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__

#include "../system.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut::engine
{
    class CKinematics2DSystem : public ISystem
    {
    private:
        ecs::CEntityQuery *m_kinematicQuery;
        
    public:
        CKinematics2DSystem( CEngine& engine );
        ~CKinematics2DSystem();

        void update( float deltaTime ) override;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_KINEMATICS2D_SYSTEM_H__