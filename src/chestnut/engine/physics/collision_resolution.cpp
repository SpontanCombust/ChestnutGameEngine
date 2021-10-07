#include "collision_resolution.hpp"

#include <algorithm> // min_element, min, clamp

namespace chestnut::engine
{    
    bool resolvePoint2DVsAABB2D( SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy, SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy ) 
    {
        float dists[] = { point.x - aabb.pos.x,                 // from left side
                          aabb.pos.x + aabb.size.x - point.x,   // to right side
                          point.y - aabb.pos.y,                 // from upper side
                          aabb.pos.y + aabb.size.y - point.y }; // to lower side

        // first check if point is within the bounds of AABB
        if( dists[0] >= 0.f && dists[1] >= 0.f && dists[2] >= 0.f && dists[3] >= 0.f )
        {
            if( ( pointPolicy & ECollisionPolicyFlags::AFFECTED ) > 0 && ( aabbPolicy & ECollisionPolicyFlags::AFFECTING ) > 0 )
            {
                // checking to which side point should be shifted
                float *min = std::min_element( dists, dists + 4 );

                if( min == dists + 0 )
                {
                    point.x -= dists[0];
                }
                else if( min == dists + 1 )
                {
                    point.x += dists[1];
                }
                else if( min == dists + 2 )
                {
                    point.y -= dists[2];
                }
                else
                {
                    point.y += dists[3];
                }
            }

            return true;
        }

        return false;
    }

    bool resolvePoint2DVsCircle2D( SColliderBodyPoint2D& point, ECollisionPolicyFlags pointPolicy, SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy ) 
    {
        vec2f diff = point - circle.pos;

        if( vecMagnitude( diff ) <= circle.radius )
        {
            if( ( pointPolicy & ECollisionPolicyFlags::AFFECTED ) > 0 && ( circlePolicy & ECollisionPolicyFlags::AFFECTING ) > 0 )
            {
                // take a unit vector with direction from center of the circle to the point and scale it by circle radius
                // add it to circle's center position and you'll get the position on the edge of the circle the point to be moved to
                point = circle.pos + vecNormalized( diff ) * circle.radius;
            }
            
            return true;
        }

        return false;
    }

    bool resolveAABB2DVsAABB2D( SColliderBodyAABB2D& aabb1, ECollisionPolicyFlags aabb1Policy, SColliderBodyAABB2D& aabb2, ECollisionPolicyFlags aabb2Policy ) 
    {
        vec2f right1left2 = vec2f{ aabb2.pos.x - ( aabb1.pos.x + aabb1.size.x ), 0.f };
        vec2f left1Right2 = vec2f{ aabb2.pos.x + aabb2.size.x - aabb1.pos.x, 0.f };
        vec2f down1Up2 = vec2f{ 0.f, aabb2.pos.y - ( aabb1.pos.y + aabb1.size.y ) };
        vec2f up1Down2 = vec2f{ 0.f, aabb2.pos.y + aabb2.size.y - aabb1.pos.y };

        if( right1left2.x <= 0.f && left1Right2.x >= 0.f && down1Up2.y <= 0.f && up1Down2.y >= 0.f )
        {
            vec2f displace = std::min( { right1left2, left1Right2, down1Up2, up1Down2 }, []( const vec2f& lhs, const vec2f& rhs )
            {
                return vecMagnitude( lhs ) < vecMagnitude( rhs );
            });
            
            // if both can be moved and move other objects - move them from the center of collision by half the intersection magnitude
            if( ( aabb1Policy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING )
             && ( aabb2Policy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) )
            {
                aabb1.pos += displace * 0.5f;
                aabb2.pos -= displace * 0.5f;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( ( aabb1Policy & ECollisionPolicyFlags::AFFECTED ) > 0 && ( aabb2Policy & ECollisionPolicyFlags::AFFECTING ) > 0 )
            {
                aabb1.pos += displace;
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( ( aabb1Policy & ECollisionPolicyFlags::AFFECTING ) > 0 && ( aabb2Policy & ECollisionPolicyFlags::AFFECTED ) > 0 )
            {
                aabb2.pos -= displace;
            }
            // in any other case objects just clip through

            return true;
        }

        return false;
    }

    bool resolveAABB2DVsCircle2D( SColliderBodyAABB2D& aabb, ECollisionPolicyFlags aabbPolicy, SColliderBodyCircle2D& circle, ECollisionPolicyFlags circlePolicy ) 
    {
        // Made with the help of https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection
        // FIXME This is an incomplete algorithm that can't properly handle situations when circle's centre is inside AABB

        vec2f aabbHalfExtents = aabb.size * 0.5f;
        vec2f aabbCenter = aabb.pos + aabbHalfExtents;
        vec2f diff = circle.pos - aabbCenter;

        vec2f clamped { std::clamp( diff.x, -aabbHalfExtents.x, aabbHalfExtents.x ),
                        std::clamp( diff.y, -aabbHalfExtents.y, aabbHalfExtents.y ) };

        vec2f closest = aabbCenter + clamped;
        diff = closest - circle.pos;

        float mag = vecMagnitude( diff );

        if( mag <= circle.radius )
        {
            vec2f displaceFull = vecNormalized( diff ) * ( circle.radius - mag );

            if( ( aabbPolicy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING )
             && ( circlePolicy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) )
            {
                aabb.pos += displaceFull * 0.5f;
                circle.pos -= displaceFull * 0.5f;    
            }
            else if( ( aabbPolicy & ECollisionPolicyFlags::AFFECTED ) > 0 && ( circlePolicy & ECollisionPolicyFlags::AFFECTING ) > 0 )
            {
                aabb.pos += displaceFull;
            }
            else if( ( aabbPolicy & ECollisionPolicyFlags::AFFECTING ) > 0 && ( circlePolicy & ECollisionPolicyFlags::AFFECTED ) > 0 )
            {
                circle.pos -= displaceFull;
            }

            return true;
        }

        return false;
    }

    bool resolveCircle2DVsCircle2D( SColliderBodyCircle2D& circle1, ECollisionPolicyFlags circle1Policy, SColliderBodyCircle2D& circle2, ECollisionPolicyFlags circle2Policy ) 
    {
        vec2f diff = circle2.pos - circle1.pos;
        vec2f diffNorm = vecNormalized( diff );
        float diffMagn = vecMagnitude( diff );
        float intersectMagn = circle1.radius + circle2.radius - diffMagn;

        if( diffMagn <= circle1.radius + circle2.radius )
        {
            // if both can be moved and move other objects - move them from the center of collision by half the intersection magnitude
            if( ( circle1Policy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) 
             && ( circle2Policy & ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) ) == ( ECollisionPolicyFlags::AFFECTED | ECollisionPolicyFlags::AFFECTING ) )
            {
                vec2f displace = ( intersectMagn / 2.f ) * diffNorm;
                circle1.pos -= displace;
                circle2.pos += displace;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( ( circle1Policy & ECollisionPolicyFlags::AFFECTED ) > 0 && ( circle2Policy & ECollisionPolicyFlags::AFFECTING ) > 0 )
            {
                circle1.pos -= intersectMagn * diffNorm;
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( ( circle1Policy & ECollisionPolicyFlags::AFFECTING ) > 0 && ( circle2Policy & ECollisionPolicyFlags::AFFECTED ) > 0 )
            {
                circle2.pos += intersectMagn * diffNorm;
            }
            // in any other case objects just clip through

            return true;
        }

        return false;
    }

} // namespace chestnut::engine
