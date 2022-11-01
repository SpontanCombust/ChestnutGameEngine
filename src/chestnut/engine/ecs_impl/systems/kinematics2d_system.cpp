#include "kinematics2d_system.hpp"

#include "../../main/engine.hpp"
#include "../components/transform2d_component.hpp"
#include "../components/kinematics2d_component.hpp"

namespace chestnut::engine
{
    CKinematics2DSystem::CKinematics2DSystem( CEngine& engine ) 
    : ISystem( engine ) 
    {
        m_kinematicQuery = getEngine().getEntityWorld().createQuery( 
            ecs::makeEntitySignature< CTransform2DComponent, CKinematics2DComponent >()
        );
    }

    CKinematics2DSystem::~CKinematics2DSystem() 
    {
        getEngine().getEntityWorld().destroyQuery( m_kinematicQuery );
    }

    void CKinematics2DSystem::update( float deltaTime ) 
    {
        getEngine().getEntityWorld().queryEntities( m_kinematicQuery );

        m_kinematicQuery->forEach(std::function(
            [deltaTime]( CTransform2DComponent& transform, CKinematics2DComponent& kinematic )
            {
                kinematic.linearVelocity  += deltaTime * kinematic.linearAcceleration;
                kinematic.angularVelocity += deltaTime * kinematic.angularAcceleration;

                transform.position += deltaTime * kinematic.linearVelocity;
                transform.rotation += deltaTime * kinematic.angularVelocity; 
            }
        ));
    }

} // namespace chestnut::engine
