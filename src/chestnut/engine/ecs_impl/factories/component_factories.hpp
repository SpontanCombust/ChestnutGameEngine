#pragma once


#include <chestnut/ecs/types.hpp>

namespace chestnut::engine
{
    // These are not your textbook definitions of factories, but their purpose is the same   

    bool componentFactory_CAnimation2DComponent(ecs::entityid_t entity);
    bool componentFactory_CCollision2DComponent(ecs::entityid_t entity);
    bool componentFactory_CIdentityComponent(ecs::entityid_t entity);
    bool componentFactory_CKinematics2DComponent(ecs::entityid_t entity);
    bool componentFactory_CModel2DComponent(ecs::entityid_t entity);
    bool componentFactory_CRenderLayerComponent(ecs::entityid_t entity);
    bool componentFactory_CSpriteComponent(ecs::entityid_t entity);
    bool componentFactory_CTimerComponent(ecs::entityid_t entity);
    bool componentFactory_CTransform2DComponent(ecs::entityid_t entity);

} // namespace chestnut::engine
