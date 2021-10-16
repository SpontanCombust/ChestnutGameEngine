#ifndef __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__
#define __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__

#include "collider.hpp"

namespace chestnut::engine
{
    // ============ very simplistics static collision resolution functions, which don't take momentum into account ============ //


    // Returns true if collision happened
    // aabbPos describes world position of the center of AABB 
    // AFFECTING flag is ignored for the point
    bool resolvePoint2DVsAABB2D( vec2f& pointPos, ECollisionPolicyFlags pointPolicy, vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy );

    // Returns true if collision happened
    // circlePos describes world position of the center of the circle
    // AFFECTING flag is ignored for the point
    bool resolvePoint2DVsCircle2D( vec2f& pointPos, ECollisionPolicyFlags pointPolicy, vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy );


    // Returns true if collision happened
    // aabbPos describes world position of the center of AABB 
    // AFFECTING flag is ignored for the point
    inline bool resolveAABB2DVsPoint2D( vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy, vec2f& pointPos, ECollisionPolicyFlags pointPolicy ) { return resolvePoint2DVsAABB2D( pointPos, pointPolicy, aabbPos, aabbScale, aabbBody, aabbPolicy ); }

    // Returns true if collision happened
    // aabbPos describes world position of the center of AABB 
    bool resolveAABB2DVsAABB2D( vec2f& aabb1Pos, const vec2f& aabb1Scale, const SColliderBodyAABB2D& aabb1Body, ECollisionPolicyFlags aabb1Policy, vec2f& aabb2Pos, const vec2f& aabb2Scale, const SColliderBodyAABB2D& aabb2Body, ECollisionPolicyFlags aabb2Policy );

    // Returns true if collision happened
    // aabbPos describes world position of the center of AABB 
    // circlePos describes world position of the center of the circle
    bool resolveAABB2DVsCircle2D( vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy, vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy );
    

    // Returns true if collision happened
    // circlePos describes world position of the center of the circle
    // AFFECTING flag is ignored for the point
    inline bool resolveCircle2DVsPoint2D( vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy, vec2f& pointPos, ECollisionPolicyFlags pointPolicy ) { return resolvePoint2DVsCircle2D( pointPos, pointPolicy, circlePos, circleScale, circleBody, circlePolicy ); }

    // Returns true if collision happened
    // circlePos describes world position of the center of the circle
    // aabbPos describes world position of the center of AABB 
    inline bool resolveCircle2DVsAABB2D( vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy, vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy ) { return resolveAABB2DVsCircle2D( aabbPos, aabbScale, aabbBody, aabbPolicy, circlePos, circleScale, circleBody, circlePolicy ); }

    // Returns true if collision happened
    // circlePos describes world position of the center of the circle
    bool resolveCircle2DVsCircle2D( vec2f& circle1Pos, float circle1Scale, const SColliderBodyCircle2D& circle1Body, ECollisionPolicyFlags circle1Policy, vec2f& circle2Pos, float circle2Scale, const SColliderBodyCircle2D& circle2Body, ECollisionPolicyFlags circle2Policy );

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLISION_RESOLUTION_H__