#include "kinematics_system.hpp"

namespace chestnut
{
    CKinematicsSystem::CKinematicsSystem(CEngine& engine ) 
    : ISystem( engine ) 
    {
        m_transformKinematicQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransformComponent>() && sign.has<CKinematicsComponent>();
        };
    }

    void CKinematicsSystem::update( uint32_t deltaTime ) 
    {
        float dt = (float)deltaTime / 1000.f;

        getEngine().getEntityWorld().queryEntities( m_transformKinematicQuery );

        ecs::forEachEntityInQuery< CTransformComponent, CKinematicsComponent >( m_transformKinematicQuery,
        [dt]( CTransformComponent& transform, CKinematicsComponent& kinematic )
        {
            kinematic.linearVelocity += dt * kinematic.linearAcceleration;
            kinematic.angularVelocity += dt * kinematic.angularAcceleration;

            transform.position += dt * kinematic.linearVelocity;
            transform.rotation += dt * kinematic.angularVelocity; 
        });
    }

} // namespace chestnut
