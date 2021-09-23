#include "kinematics_system.hpp"

#include "../../main/engine.hpp"

namespace chestnut
{
    CKinematicsSystem::CKinematicsSystem( CEngine& engine ) 
    : ISystem( engine ) 
    {
        m_transformKinematicQuery.entitySignCond = []( const ecs::CEntitySignature& sign )
        {
            return sign.has<CTransformComponent>() && sign.has<CKinematicsComponent>();
        };
    }

    void CKinematicsSystem::update( float deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_transformKinematicQuery );

        ecs::forEachEntityInQuery< CTransformComponent, CKinematicsComponent >( m_transformKinematicQuery,
        [deltaTime]( CTransformComponent& transform, CKinematicsComponent& kinematic )
        {
            kinematic.linearVelocity  += deltaTime * kinematic.linearAcceleration;
            kinematic.angularVelocity += deltaTime * kinematic.angularAcceleration;

            transform.position += deltaTime * kinematic.linearVelocity;
            transform.rotation += deltaTime * kinematic.angularVelocity; 
        });
    }

} // namespace chestnut
