#ifndef __CHESTNUT_KINEMATICS_SYSTEM_H__
#define __CHESTNUT_KINEMATICS_SYSTEM_H__

#include "../component_system.hpp"
#include "../components/transform_component.hpp"
#include "../components/kinematics_component.hpp"

namespace chestnut
{
    class CKinematicsSystem : public IComponentSystem
    {
    private:
        ecs::SEntityQuery m_transformKinematicQuery;
        
    public:
        void initQueries() override;

        void update( uint32_t deltaTime ) override;
    };

} // namespace chestnut

#endif // __CHESTNUT_KINEMATICS_SYSTEM_H__