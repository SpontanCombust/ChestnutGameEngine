#ifndef __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__
#define __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__

#include "collider.hpp"

namespace chestnut::engine
{
    // ============ very simplistics static collision resolution functions, which don't take momentum into account ============ //


    // Returns true if collision happened
    // AFFECTING flag is ignored for the point
    bool resolvePoint2DVsAABB2D( SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy, SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy );

    // Returns true if collision happened
    // AFFECTING flag is ignored for the point
    bool resolvePoint2DVsCircle2D( SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy, SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy );


    // Returns true if collision happened
    // AFFECTING flag is ignored for the point
    inline bool resolveAABB2DVsPoint2D( SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy, SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy ) { return resolvePoint2DVsAABB2D( point, pointPolicy, aabb, aabbPolicy ); }

    // Returns true if collision happened
    bool resolveAABB2DVsAABB2D( SColliderBodyAABB2D& aabb1, ECollisionPolicyFlags aabb1Policy, SColliderBodyAABB2D& aabb2, ECollisionPolicyFlags aabb2Policy );

    // Returns true if collision happened
    bool resolveAABB2DVsCircle2D( SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy, SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy );
    

    // Returns true if collision happened
    // AFFECTING flag is ignored for the point
    inline bool resolveCircle2DVsPoint2D( SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy, SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy ) { return resolvePoint2DVsCircle2D( point, pointPolicy, circle, circlePolicy ); }

    inline bool resolveCircle2DVsAABB2D( SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy, SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy ) { return resolveAABB2DVsCircle2D( aabb, aabbPolicy, circle, circlePolicy ); }

    bool resolveCircle2DVsCircle2D( SColliderBodyCircle2D& circle1, ECollisionPolicyFlags circle1Policy, SColliderBodyCircle2D& circle2, ECollisionPolicyFlags circle2Policy );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__