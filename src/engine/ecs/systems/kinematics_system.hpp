#ifndef __CHESTNUT_KINEMATICS_SYSTEM_H__
#define __CHESTNUT_KINEMATICS_SYSTEM_H__

#include "../system.hpp"
#include "../components/transform_component.hpp"
#include "../components/kinematics_component.hpp"

#include <chestnut/ecs/entity_query.hpp>

namespace chestnut
{
    class CKinematicsSystem : public ISystem
    {
    private:
        ecs::SEntityQuery m_transformKinematicQuery;
        
    public:
        CKinematicsSystem( CEngine& engine );

        void update( uint32_t deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_KINEMATICS_SYSTEM_H__