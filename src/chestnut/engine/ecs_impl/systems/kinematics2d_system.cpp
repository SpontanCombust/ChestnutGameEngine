#include "chestnut/engine/ecs_impl/systems/kinematics2d_system.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"

namespace chestnut::engine
{
    CKinematics2DSystem::CKinematics2DSystem(systempriority_t priority) 
    : ILogicSystem(priority) 
    {
        m_kinematicQuery = CEngine::getInstance().getEntityWorld().createQuery( 
            ecs::makeEntitySignature< CTransform2DComponent, CKinematics2DComponent >()
        );
    }

    CKinematics2DSystem::~CKinematics2DSystem() 
    {
        CEngine::getInstance().getEntityWorld().destroyQuery( m_kinematicQuery );
    }

    void CKinematics2DSystem::update( float deltaTime ) 
    {
        CEngine::getInstance().getEntityWorld().queryEntities( m_kinematicQuery );

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
