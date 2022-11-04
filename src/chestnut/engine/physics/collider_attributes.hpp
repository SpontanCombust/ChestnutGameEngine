#pragma once


#include "chestnut/engine/macros.hpp"
#include "../misc/flags.hpp"

namespace chestnut::engine
{
    // Enum for optimizing object pairing to weed out collision checks between objects that will never collide or collision between them doesn't matter at all
    enum class EColliderActivity
    {
        STATIC, // object is typically staying in the same place
        DYNAMIC // object can move around
    };

    // Flags describing how a collider object should interact with other objects
    enum class ECollisionPolicyFlags
    {
        // do nothing about the collision
        NONE        = 1,
        // if object's position can be affected by the other collider
        // used for objects that are meant to move around frequently
        AFFECTED    = 2,
        // disallows object's position to be affected during collision
        // used for objects that move rarely, not at all or those which should follow very specific path
        // note that if both objects are blocking none of them will be adjusted and they'll clip through each other
        AFFECTING   = 4, 
        // if should raise and event about the collision if it happens
        TRIGGER     = 8
    };

    DECLARE_ENUM_FLAG_OPERATORS( ECollisionPolicyFlags )

} // namespace chestnut::engine


