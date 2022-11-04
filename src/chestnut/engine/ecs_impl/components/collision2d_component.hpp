#pragma once

#include "chestnut/engine/macros.hpp"
#include "../../physics/collider2d.hpp"

#include <memory>


namespace chestnut::engine
{
    struct CHESTNUT_API CCollision2DComponent
    {
        std::unique_ptr<CCollider2D> collider;

        CCollision2DComponent() = default;
    };

} // namespace chestnut::engine
