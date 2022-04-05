#ifndef __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__
#define __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__

#include "../../physics/collider2d.hpp"

#include <memory>


namespace chestnut::engine
{
    struct CCollision2DComponent
    {
        std::unique_ptr<CCollider2D> collider;

        CCollision2DComponent() = default;
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION2D_COMPONENT_H__