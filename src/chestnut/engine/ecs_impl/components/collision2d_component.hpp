#pragma once


#include "chestnut/engine/physics/collider2d.hpp"

#include <variant>

namespace chestnut::engine
{
    using VCollider2D = std::variant<
        CBoxCollider2D,
        CPointCollider2D,
        CCircleCollider2D
    >;

    struct CCollision2DComponent
    {
        // Could've used a pointer here, but like this all the memory for these colliders
        // is fully contiguous in the entity world
        VCollider2D colliderVariant;
        bool colliderOutline = false;

        CCollision2DComponent() = default;

        // Returns the value of the colliderVariant, but casted onto base class
        CHESTNUT_API CCollider2D& getBaseCollider();
        // Returns the value of the colliderVariant, but casted onto base class
        CHESTNUT_API const CCollider2D& getBaseCollider() const;
    };

} // namespace chestnut::engine
