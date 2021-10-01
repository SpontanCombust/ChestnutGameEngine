#include "kinematics2d_system.hpp"

#include "../../main/engine.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/kinematics2d_component.hpp"

namespace chestnut::engine
{
    CKinematics2DSystem::CKinematics2DSystem( CEngine& engine ) 
    : ISystem( engine ) 
    {
        m_transformKinematicQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransform2DComponent>() && sign.has<CKinematics2DComponent>();
        };
    }

    void CKinematics2DSystem::update( float deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_transformKinematicQuery );

        ecs::forEachEntityInQuery< CTransform2DComponent, CKinematics2DComponent >( m_transformKinematicQuery,
        [deltaTime]( CTransform2DComponent& transform, CKinematics2DComponent& kinematic )
        {
            kinematic.linearVelocity  += deltaTime * kinematic.linearAcceleration;
            kinematic.angularVelocity += deltaTime * kinematic.angularAcceleration;

            transform.position += deltaTime * kinematic.linearVelocity;
            transform.rotation += deltaTime * kinematic.angularVelocity; 
        });
    }

} // namespace chestnut::engine
