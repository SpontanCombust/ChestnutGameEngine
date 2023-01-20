#include "chestnut/engine/physics/collider2d_collision_detection.hpp"

#include <algorithm> // clamp

namespace chestnut::engine
{  
    inline bool canAffect( CFlags<ECollisionPolicy> policyFlags )
    {
        return policyFlags & ECollisionPolicy::AFFECTING;
    }

    inline bool canBeAffected( CFlags<ECollisionPolicy> policyFlags )
    {
        return policyFlags & ECollisionPolicy::AFFECTED;
    }

    inline bool canAffectOrBeAffected( CFlags<ECollisionPolicy> policyFlags )
    {
        return policyFlags & CFlags{ECollisionPolicy::AFFECTING, ECollisionPolicy::AFFECTED};
    }

    inline bool canAffectAndBeAffected( CFlags<ECollisionPolicy> policyFlags )
    {
        CFlags f = {ECollisionPolicy::AFFECTING, ECollisionPolicy::AFFECTED};
        return (policyFlags & f) == f;
    }




    SCollisionResolutionData checkPointVsBox(const CPointCollider2D& point, const CBoxCollider2D& box)
    {
        SCollisionResolutionData crd {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};

        const vec2f boxHalfExtents = box.getRealSize() / 2.f;
        const vec2f pointToBoxCentre = box.getPosition() - point.getPosition();

        if( std::abs( pointToBoxCentre.x ) <= boxHalfExtents.x && std::abs( pointToBoxCentre.y ) <= boxHalfExtents.y )
        {
            crd.isCollision = true;
        
            if( canBeAffected(point.getPolicyFlags()) && canAffect(box.getPolicyFlags()) )
            {
                vec2f displace1 {0.0f, 0.0f};

                if( pointToBoxCentre.x >= 0.f ) // points from left (X-) to center
                {
                    displace1.x = pointToBoxCentre.x - boxHalfExtents.x;
                }
                else
                {
                    displace1.x = pointToBoxCentre.x + boxHalfExtents.x;
                }

                if( pointToBoxCentre.y >= 0.f ) // points from up (Y-) to center
                {
                    displace1.y = pointToBoxCentre.y - boxHalfExtents.y;
                }
                else
                {
                    displace1.y = pointToBoxCentre.y + boxHalfExtents.y;
                }
                
                if( std::abs( displace1.x ) < std::abs( displace1.y ) )
                {
                    displace1.y = 0.f;
                }
                else
                {
                    displace1.x = 0.f;
                }

                crd.obj1Displacement = displace1;
                // displacement for box stays zero 
            }
        }

        return crd;
    }

    SCollisionResolutionData checkPointVsCircle(const CPointCollider2D& point, const CCircleCollider2D& circle)
    {
        SCollisionResolutionData crd {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};

        const vec2f diff = point.getPosition() - circle.getPosition();

        if( vecMagnitude(diff) <= circle.getMaxRealRadius() )
        {
            crd.isCollision = true;

            if( canBeAffected(point.getPolicyFlags()) && canAffect(circle.getPolicyFlags()) )
            {
                // take a unit vector with direction from center of the circle to the point and scale it by circle radius
                // add it to circle's center position and you'll get the position on the edge of the circle the point to be moved to
                crd.obj1Displacement = circle.getPosition() + vecNormalized(diff) * circle.getMaxRealRadius() - point.getPosition();
                // displacement for circle stays zero
            }
        }

        return crd;
    }




    SCollisionResolutionData checkBoxVsPoint(const CBoxCollider2D& box, const CPointCollider2D& point)
    {
        SCollisionResolutionData crd = checkPointVsBox(point, box);
        std::swap(crd.obj1Displacement, crd.obj2Displacement);
        return crd;
    }

    SCollisionResolutionData checkBoxVsBox(const CBoxCollider2D& box1, const CBoxCollider2D& box2)
    {
        SCollisionResolutionData crd {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};

        const vec2f center1ToCenter2 = box2.getPosition() - box1.getPosition();
        const vec2f box1HalfExtents = box1.getRealSize() / 2.f;
        const vec2f box2HalfExtents = box2.getRealSize() / 2.f;

        if( std::abs( center1ToCenter2.x ) <= ( box1HalfExtents.x + box2HalfExtents.x ) && std::abs( center1ToCenter2.y ) <= ( box1HalfExtents.y + box2HalfExtents.y ) )
        {   
            crd.isCollision = true;

            if( canAffectOrBeAffected(box1.getPolicyFlags()) || canAffectOrBeAffected(box2.getPolicyFlags()) )
            {
                vec2f displace1;

                if( center1ToCenter2.x >= 0.f )
                {
                    displace1.x = center1ToCenter2.x - box1HalfExtents.x - box2HalfExtents.x;
                }
                else
                {
                    displace1.x = center1ToCenter2.x + box1HalfExtents.x + box2HalfExtents.x;   
                }
                
                if( center1ToCenter2.y >= 0.f )
                {
                    displace1.y = center1ToCenter2.y - box1HalfExtents.y - box2HalfExtents.y;
                }
                else
                {
                    displace1.y = center1ToCenter2.y + box1HalfExtents.y + box2HalfExtents.y;   
                }
                
                if( std::abs( displace1.x ) < std::abs( displace1.y ) )
                {
                    displace1.y = 0.f;
                }
                else
                {
                    displace1.x = 0.f;
                }


                if( canAffectAndBeAffected(box1.getPolicyFlags()) && canAffectAndBeAffected(box2.getPolicyFlags()) )
                {
                    crd.obj1Displacement = displace1 / 2.f;
                    crd.obj2Displacement = -displace1 / 2.f;
                }
                // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
                else if( canBeAffected(box1.getPolicyFlags()) && canAffect(box2.getPolicyFlags()) )
                {
                    crd.obj1Displacement = displace1;
                    // displacement for box2 stays zero
                }
                // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
                else if( canAffect(box1.getPolicyFlags()) && canBeAffected(box2.getPolicyFlags()) )
                {
                    // displacement for box1 stays zero
                    crd.obj2Displacement = -displace1;
                }
            }
        }

        return crd;
    }

    SCollisionResolutionData checkBoxVsCircle(const CBoxCollider2D& box, const CCircleCollider2D& circle)
    {
        // Made with the help of https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-detection

        SCollisionResolutionData crd {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};

        const vec2f boxHalfExtents = box.getRealSize() / 2.f;
        const bool canCollidersAffectOrBeAffected = canAffectOrBeAffected(box.getPolicyFlags()) || canAffectOrBeAffected(circle.getPolicyFlags());

        vec2f diffBoxToCircle = circle.getPosition() - box.getPosition();
        vec2f displaceCircle;

        // circle center is inside AABB
        if( std::abs( diffBoxToCircle.x ) <= boxHalfExtents.x && std::abs( diffBoxToCircle.y ) <= boxHalfExtents.y )
        {
            crd.isCollision = true;

            if( canCollidersAffectOrBeAffected )
            {
                if( diffBoxToCircle.x >= 0.f ) 
                {
                    displaceCircle.x = boxHalfExtents.x - diffBoxToCircle.x + circle.getMaxRealRadius();
                }
                else
                {
                    displaceCircle.x = -boxHalfExtents.x - diffBoxToCircle.x - circle.getMaxRealRadius();
                }

                if( diffBoxToCircle.y >= 0.f ) 
                {
                    displaceCircle.y = boxHalfExtents.y - diffBoxToCircle.y + circle.getMaxRealRadius();
                }
                else
                {
                    displaceCircle.y = -boxHalfExtents.y - diffBoxToCircle.y - circle.getMaxRealRadius();
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
            const vec2f clamped { std::clamp( diffBoxToCircle.x, -boxHalfExtents.x, boxHalfExtents.x ),
                                  std::clamp( diffBoxToCircle.y, -boxHalfExtents.y, boxHalfExtents.y ) };

            const vec2f closest = box.getPosition() + clamped;
            diffBoxToCircle = circle.getPosition() - closest;

            const float diffMag = vecMagnitude( diffBoxToCircle );

            if( diffMag <= circle.getMaxRealRadius() )
            {  
                crd.isCollision = true;

                if( canCollidersAffectOrBeAffected )
                {
                    displaceCircle = vecNormalized( diffBoxToCircle ) * ( circle.getMaxRealRadius() - diffMag );
                }
            }
            else
            {
                crd.isCollision = false;   
            }
        }

        if( crd.isCollision && canCollidersAffectOrBeAffected )
        {
            if( canAffectAndBeAffected(box.getPolicyFlags()) && canAffectAndBeAffected(circle.getPolicyFlags()) )
            {
                crd.obj1Displacement = -displaceCircle / 2.f;
                crd.obj2Displacement = displaceCircle / 2.f;    
            }
            else if( canBeAffected(box.getPolicyFlags()) && canAffect(circle.getPolicyFlags()) )
            {
                crd.obj1Displacement = -displaceCircle;
                // displacement for circle stays zero
            }
            else if( canAffect(box.getPolicyFlags()) && canBeAffected(circle.getPolicyFlags()) )
            {
                // displacement for box stays zero
                crd.obj2Displacement = displaceCircle;
            }
        }

        return crd;
    }




    SCollisionResolutionData checkCircleVsPoint(const CCircleCollider2D& circle, const CPointCollider2D& point)
    {
        auto crd = checkPointVsCircle(point, circle);
        std::swap(crd.obj1Displacement, crd.obj2Displacement);
        return crd;
    }

    SCollisionResolutionData checkCircleVsBox(const CCircleCollider2D& circle, const CBoxCollider2D& box)
    {
        auto crd = checkBoxVsCircle(box, circle);
        std::swap(crd.obj1Displacement, crd.obj2Displacement);
        return crd;
    }

    SCollisionResolutionData checkCircleVsCircle(const CCircleCollider2D& circle1, const CCircleCollider2D& circle2)
    {
        SCollisionResolutionData crd {false, vec2f(0.0f, 0.0f), vec2f(0.0f, 0.0f)};

        const vec2f diff = circle2.getPosition() - circle1.getPosition();
        const float diffMagn = vecMagnitude(diff);
        const float radiusSum = circle1.getMaxRealRadius() + circle2.getMaxRealRadius();
        const float intersectMagn = radiusSum - diffMagn;
        
        if( intersectMagn >= 0.f )
        {
            crd.isCollision = true;

            vec2f diffNorm = vecNormalized( diff );

            // if both can be moved and move other objects - move them from the center of collision by half the intersection magnitude
            if( canAffectAndBeAffected( circle1.getPolicyFlags() ) && canAffectAndBeAffected( circle2.getPolicyFlags() ) )
            {
                vec2f displace = ( intersectMagn / 2.f ) * diffNorm;
                crd.obj1Displacement = -displace;
                crd.obj2Displacement = displace;
            }
            // if only the first one is to be moved by the second one - move the 1st one away from 2nd one's way
            else if( canBeAffected( circle1.getPolicyFlags() ) && canAffect( circle2.getPolicyFlags() ) )
            {
                crd.obj1Displacement = -intersectMagn * diffNorm;
                // displacement for circle2 stays zero
            }
            // if only the first one is supposed to move second object - move the 2nd one away from 1st one's way
            else if( canAffect( circle1.getPolicyFlags() ) && canBeAffected( circle2.getPolicyFlags() ) )
            {
                // displacement for circle1 stays zero
                crd.obj2Displacement = intersectMagn * diffNorm;
            }
            // in any other case objects just clip through
        }

        return crd;
    }

} // namespace chestnut::engine
