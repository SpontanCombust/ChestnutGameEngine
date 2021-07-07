#include "kinematics_system.hpp"

namespace chestnut
{
    void CKinematicsSystem::submitComponents( CComponentBatch *batch ) 
    {
        SComponentSetSignature sign = batch->getSignature();

        if( sign.includes<STransformComponent>() && sign.includes<SKinematicsComponent>() )
        {
            batch->getComponentsAppendToVec( m_vecTransformComps );
            batch->getComponentsAppendToVec( m_vecKinematicComps );
        }
    }

    void CKinematicsSystem::clearComponents() 
    {
        m_vecTransformComps.clear();
        m_vecKinematicComps.clear();
    }

    void CKinematicsSystem::update( uint32_t deltaTime ) 
    {
        STransformComponent *transfComp;
        SKinematicsComponent *kinemComp;

        float dt = (float)deltaTime / 1000.f;

        size_t entityCount = m_vecTransformComps.size();
        for (size_t i = 0; i < entityCount; i++)
        {
            transfComp = m_vecTransformComps[i];
            kinemComp = m_vecKinematicComps[i];

            kinemComp->linearVelocity += dt * kinemComp->linearAcceleration;
            kinemComp->angularVelocity += dt * kinemComp->angularAcceleration;

            transfComp->position += dt * kinemComp->linearVelocity;
            transfComp->rotation += dt * kinemComp->angularVelocity;
        }
    }

} // namespace chestnut
