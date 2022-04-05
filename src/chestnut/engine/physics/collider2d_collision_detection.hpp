#ifndef __CHESTNUT_ENGINE_COLLIDER2D_COLLISION_DETECTION_H__
#define __CHESTNUT_ENGINE_COLLIDER2D_COLLISION_DETECTION_H__

#include "collider2d.hpp"

namespace chestnut::engine
{
    // ============ very simplistics static collision resolution functions, which don't take momentum into account ============ //


    // AFFECTING flag is ignored for the point
    SCollisionResolutionData checkPointVsBox(const CPointCollider2D& point, const CBoxCollider2D& box);

    // AFFECTING flag is ignored for the point
    SCollisionResolutionData checkPointVsCircle(const CPointCollider2D& point, const CCircleCollider2D& circle);

    // Point vs Point collision doesn't happen


    // AFFECTING flag is ignored for the point
    SCollisionResolutionData checkBoxVsPoint(const CBoxCollider2D& box, const CPointCollider2D& point);

    SCollisionResolutionData checkBoxVsBox(const CBoxCollider2D& box1, const CBoxCollider2D& box2);

    SCollisionResolutionData checkBoxVsCircle(const CBoxCollider2D& box, const CCircleCollider2D& circle);
    

    SCollisionResolutionData checkCircleVsPoint(const CCircleCollider2D& circle, const CPointCollider2D& point);

    SCollisionResolutionData checkCircleVsBox(const CCircleCollider2D& circle, const CBoxCollider2D& box);

    SCollisionResolutionData checkCircleVsCircle(const CCircleCollider2D& circle1, const CCircleCollider2D& circle2);

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLLIDER2D_COLLISION_DETECTION_H__