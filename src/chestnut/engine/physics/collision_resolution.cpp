#include "collision_resolution.hpp"

#include <algorithm> // clamp

namespace chestnut::engine
{  
    inline bool canAffect( ECollisionPolicyFlags policyFlags )
    {
        return ( policyFlags & ECollisionPolicyFlags::AFFECTING ) > 0;
    }

    inline bool canBeAffected( ECollisionPolicyFlags policyFlags )
    {
        return ( policyFlags & ECollisionPolicyFlags::AFFECTED ) > 0;
    }

    inline bool canAffectOrBeAffected( ECollisionPolicyFlags policyFlags )
    {
        return ( policyFlags & ( ECollisionPolicyFlags::AFFECTING | ECollisionPolicyFlags::AFFECTED ) ) > 0;
    }

    inline bool canAffectAndBeAffected( ECollisionPolicyFlags policyFlags )
    {
        return ( policyFlags & ( ECollisionPolicyFlags::AFFECTING | ECollisionPolicyFlags::AFFECTED ) ) == ( ECollisionPolicyFlags::AFFECTING | ECollisionPolicyFlags::AFFECTED );
    }

    bool resolvePoint2DVsAABB2D( vec2f& pointPos, ECollisionPolicyFlags pointPolicy, vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy )
    {
        vec2f aabbHalfExtents = aabbBody.size * aabbScale / 2.f;
        vec2f pointToAABBCentre = aabbPos - pointPos;

        if( std::abs( pointToAABBCentre.x ) <= aabbHalfExtents.x && std::abs( pointToAABBCentre.y ) <= aabbHalfExtents.y )
        {
            if( canBeAffected( pointPolicy ) && canAffect( aabbPolicy ) )
            {
                vec2f displace;
    
                if( pointToAABBCentre.x >= 0.f ) // points from left (X-) to center
                {
                    displace.x = pointToAABBCentre.x - aabbHalfExtents.x;
                }
                else
                {
                    displace.x = pointToAABBCentre.x + aabbHalfExtents.x;
                }

                if( pointToAABBCentre.y >= 0.f ) // points from up (Y-) to center
                {
                    displace.y = pointToAABBCentre.y - aabbHalfExtents.y;
                }
                else
                {
                    displace.y = pointToAABBCentre.y + aabbHalfExtents.y;
                }
                
                if( std::abs( displace.x ) < std::abs( displace.y ) )
                {
                    pointPos.x += displace.x;
                }
                else
                {
                    pointPos.y += displace.y;
                }    
            }

            return true;   
        }

        return false;
    }

    bool resolvePoint2DVsCircle2D( vec2f& pointPos, ECollisionPolicyFlags pointPolicy, vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy )
    {
        vec2f diff = pointPos - circlePos;

        if( vecMagnitude( diff ) <= ( circleBody.radius * circleScale ) )
        {
            if( canBeAffected( pointPolicy ) && canAffect( circlePolicy ) )
            {
                // take a unit vector with direction from center of the circle to the point and scale it by circle radius
                // add it to circle's center position and you'll get the position on the edge of the circle the point to be moved to
                pointPos = circlePos + vecNormalized( diff ) * ( circleBody.radius * circleScale );
            }
            
            return true;
        }

        return false;
    }

    bool resolveAABB2DVsAABB2D( vec2f& aabb1Pos, const vec2f& aabb1Scale, const SColliderBodyAABB2D& aabb1Body, ECollisionPolicyFlags aabb1Policy, vec2f& aabb2Pos, const vec2f& aabb2Scale, const SColliderBodyAABB2D& aabb2Body, ECollisionPolicyFlags aabb2Policy )
    {
        vec2f center1ToCenter2 = aabb2Pos - aabb1Pos;
        vec2f aabb1HalfExtents = aabb1Body.size * aabb1Scale / 2.f;
        vec2f aabb2HalfExtents = aabb2Body.size * aabb2Scale / 2.f;

        if( std::abs( center1ToCenter2.x ) <= ( aabb1HalfExtents.x + aabb2HalfExtents.x ) && std::abs( center1ToCenter2.y ) <= ( aabb1HalfExtents.y + aabb2HalfExtents.y ) )
        {   
            if( canAffectOrBeAffected( aabb1Policy ) || canAffectOrBeAffected( aabb2Policy ) )
            {
                vec2f displaceAABB1;

                if( center1ToCenter2.x >= 0.f )
                {
                    displaceAABB1.x = center1ToCenter2.x - aabb1HalfExtents.x - aabb2HalfExtents.x;
                }
                else
                {
                    displaceAABB1.x = center1ToCenter2.x + aabb1HalfExtents.x + aabb2HalfExtents.x;   
                }
                
                if( center1ToCenter2.y >= 0.f )
                {
                    displaceAABB1.y = center1ToCenter2.y - aabb1HalfExtents.y - aabb2HalfExtents.y;
                }
                else
                {
                    displaceAABB1.y = center1ToCenter2.y + aabb1HalfExtents.y + aabb2HalfExtents.y;   
                }
                
                if( std::abs( displaceAABB1.x ) < std::abs( displaceAABB1.y ) )
                {
                    displaceAABB1.y = 0.f;
                }
                else
                {
                    displaceAABB1.x = 0.f;
                }


                if( canAffectAndBeAffected( aabb1Policy ) && canAffectAndBeAffected( aabb2Policy ) )
                {
                    aabb1Pos += displaceAABB1 / 2.f;
                    aabb2Pos -= displaceAABB1 / 2.f;
                }
                // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
                else if( canBeAffected( aabb1Policy ) && canAffect( aabb2Policy ) )
                {
                    aabb1Pos += displaceAABB1;
                }
                // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
                else if( canAffect( aabb1Policy ) && canBeAffected( aabb2Policy ) )
                {
                    aabb2Pos -= displaceAABB1;
                }
            }

            return true;
        }

        return false;
    }

    bool resolveAABB2DVsCircle2D( vec2f& aabbPos, const vec2f& aabbScale, const SColliderBodyAABB2D& aabbBody, ECollisionPolicyFlags aabbPolicy, vec2f& circlePos, float circleScale, const SColliderBodyCircle2D& circleBody, ECollisionPolicyFlags circlePolicy )
    {
        // Made with the help of https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

        vec2f aabbHalfExtents = aabbBody.size * aabbScale / 2.f;
        vec2f diffAABBToCircle = circlePos - aabbPos;

        bool canCollidersAffectOrBeAffected = canAffectOrBeAffected( aabbPolicy ) || canAffectOrBeAffected( circlePolicy );
        vec2f displaceCircle;
        bool isCollision;

        // circle center is inside AABB
        if( std::abs( diffAABBToCircle.x ) <= aabbHalfExtents.x && std::abs( diffAABBToCircle.y ) <= aabbHalfExtents.y )
        {
            isCollision = true;

            if( canCollidersAffectOrBeAffected )
            {
                if( diffAABBToCircle.x >= 0.f ) 
                {
                    displaceCircle.x = aabbHalfExtents.x - diffAABBToCircle.x + circleBody.radius * circleScale;
                }
                else
                {
                    displaceCircle.x = -aabbHalfExtents.x - diffAABBToCircle.x - circleBody.radius * circleScale;
                }

                if( diffAABBToCircle.y >= 0.f ) 
                {
                    displaceCircle.y = aabbHalfExtents.y - diffAABBToCircle.y + circleBody.radius * circleScale;
                }
                else
                {
                    displaceCircle.y = -aabbHalfExtents.y - diffAABBToCircle.y - circleBody.radius * circleScale;
                }
                
                if( std::abs( displaceCircle.x ) < std::abs( displaceCircle.y ) )
                {
                    displaceCircle.y = 0.f;
                }
                else
                {
                    displaceCircle.x = 0.f;
                }   
            }
        }
        // circle center is outside of AABB
        else
        {
            // direction vector coming from AABB center to circle center clamped to fit inside AABB's bounds
            vec2f clamped { std::clamp( diffAABBToCircle.x, -aabbHalfExtents.x, aabbHalfExtents.x ),
                            std::clamp( diffAABBToCircle.y, -aabbHalfExtents.y, aabbHalfExtents.y ) };

            vec2f closest = aabbPos + clamped;
            diffAABBToCircle = circlePos - closest;

            float diffMag = vecMagnitude( diffAABBToCircle );

            if( diffMag <= circleBody.radius * circleScale )
            {  
                isCollision = true;

                if( canCollidersAffectOrBeAffected )
                {
                    displaceCircle = vecNormalized( diffAABBToCircle ) * ( circleBody.radius * circleScale - diffMag );
                }
            }
            else
            {
                isCollision = false;   
            }
        }

        if( isCollision && canCollidersAffectOrBeAffected )
        {
            if( canAffectAndBeAffected( aabbPolicy ) && canAffectAndBeAffected( circlePolicy ) )
            {
                circlePos += displaceCircle / 2.f;    
                aabbPos -= displaceCircle / 2.f;
            }
            else if( canBeAffected( aabbPolicy ) && canAffect( circlePolicy ) )
            {
                aabbPos -= displaceCircle;
            }
            else if( canAffect( aabbPolicy ) && canBeAffected( circlePolicy ) )
            {
                circlePos += displaceCircle;
            }
        }

        return isCollision;
    }

    bool resolveCircle2DVsCircle2D( vec2f& circle1Pos, float circle1Scale, const SColliderBodyCircle2D& circle1Body, ECollisionPolicyFlags circle1Policy, vec2f& circle2Pos, float circle2Scale, const SColliderBodyCircle2D& circle2Body, ECollisionPolicyFlags circle2Policy )
    {
        vec2f diff = circle2Pos - circle1Pos;
        float diffMagn = vecMagnitude( diff );
        float radiusSum = circle1Body.radius * circle1Scale + circle2Body.radius  * circle2Scale;
        float intersectMagn = radiusSum - diffMagn;
        
        if( intersectMagn >= 0.f )
        {
            vec2f diffNorm = vecNormalized( diff );

            // if both can be moved and move other objects - move them from the center of collision by half the intersection magnitude
            if( canAffectAndBeAffected( circle1Policy ) && canAffectAndBeAffected( circle2Policy ) )
            {
                vec2f displace = ( intersectMagn / 2.f ) * diffNorm;
                circle1Pos -= displace;
                circle2Pos += displace;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( canBeAffected( circle1Policy ) && canAffect( circle2Policy ) )
            {
                circle1Pos -= intersectMagn * diffNorm;
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( canAffect( circle1Policy ) && canBeAffected( circle2Policy ) )
            {
                circle2Pos += intersectMagn * diffNorm;
            }
            // in any other case objects just clip through

            return true;
        }

        return false;
    }

} // namespace chestnut::engine
