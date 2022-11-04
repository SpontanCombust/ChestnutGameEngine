#pragma once


#include "chestnut/engine/physics/collider2d.hpp"

#include <memory>


namespace chestnut::engine
{
    struct CCollision2DComponent
    {
        std::unique_ptr<CCollider2D> collider;

        CCollision2DComponent() = default;
    };

} // namespace chestnut::engine
