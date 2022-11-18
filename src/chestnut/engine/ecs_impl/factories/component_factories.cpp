#include "chestnut/engine/ecs_impl/factories/component_factories.hpp"

#include "chestnut/engine/main/engine.hpp"
#include "chestnut/engine/ecs_impl/components/animation2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/collision2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/kinematics2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/model2d_component.hpp"
#include "chestnut/engine/ecs_impl/components/render_layer_component.hpp"
#include "chestnut/engine/ecs_impl/components/sprite_component.hpp"
#include "chestnut/engine/ecs_impl/components/timer_component.hpp"
#include "chestnut/engine/ecs_impl/components/transform2d_component.hpp"


namespace chestnut::engine
{
    bool componentFactory_CAnimation2DComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CAnimation2DComponent>(entity);
    }
    
    bool componentFactory_CCollision2DComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CCollision2DComponent>(entity);
    }

    bool componentFactory_CKinematics2DComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CKinematics2DComponent>(entity);
    }

    bool componentFactory_CModel2DComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CModel2DComponent>(entity);
    }

    bool componentFactory_CRenderLayerComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CRenderLayerComponent>(entity);
    }

    bool componentFactory_CSpriteComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CSpriteComponent>(entity);
    }

    bool componentFactory_CTimerComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CTimerComponent>(entity);
    }

    bool componentFactory_CTransform2DComponent(ecs::entityid_t entity) noexcept
    {
        return (bool)CEngine::getInstance()
        .getEntityWorld()
        .createComponent<CTransform2DComponent>(entity);
    }


} // namespace chestnut::engine
