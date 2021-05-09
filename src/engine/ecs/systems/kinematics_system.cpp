#include "kinematics_system.hpp"

#include "../components/transform_component.hpp"
#include "../components/kinematics_component.hpp"

namespace chestnut
{
    void CKinematicsSystem::submitBatch( CComponentBatch *batch ) 
    {
        SComponentSetSignature sign = batch->getSignature();

        if( sign.includes<STransformComponent>() && sign.includes<SKinematicsComponent>() )
        {
            m_kinematicBatches.push_back( batch );
        }
    }

    void CKinematicsSystem::clearBatches() 
    {
        m_kinematicBatches.clear();
    }

    void CKinematicsSystem::update( uint32_t deltaTime ) 
    {
        std::vector<STransformComponent *> vecTransfComps;
        std::vector<SKinematicsComponent *> vecKinemComps;
        STransformComponent *transfComp;
        SKinematicsComponent *kinemComp;

        float dt = (float)deltaTime / 1000.f;

        for( CComponentBatch *batch : m_kinematicBatches )
        {
            vecTransfComps = batch->getComponents<STransformComponent>();
            vecKinemComps = batch->getComponents<SKinematicsComponent>();

            for (int i = 0; i < batch->getEntityCount(); i++)
            {
                transfComp = vecTransfComps[i];
                kinemComp = vecKinemComps[i];

                kinemComp->linearVelocity += dt * kinemComp->linearAcceleration;
                kinemComp->angularVelocity += dt * kinemComp->angularAcceleration;

                transfComp->position += dt * kinemComp->linearVelocity;
                transfComp->rotation += dt * kinemComp->angularVelocity;
            }
        }
    }

} // namespace chestnut
