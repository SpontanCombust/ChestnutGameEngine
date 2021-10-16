#ifndef __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__

#include "../../physics/collider.hpp"

#include <chestnut/ecs/component.hpp>

#include <variant>

namespace chestnut::engine
{
    typedef std::variant< SColliderBodyPoint2D,
                          SColliderBodyAABB2D,
                          SColliderBodyCircle2D > CColliderBodyVariant;

    class CCollision2DComponent : public ecs::CComponent
    {
    public:
        EColliderActivity activity;
        EColliderBodyType bodyType;
        CColliderBodyVariant bodyVariant;
        ECollisionPolicyFlags policyFlags;

        CCollision2DComponent();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__