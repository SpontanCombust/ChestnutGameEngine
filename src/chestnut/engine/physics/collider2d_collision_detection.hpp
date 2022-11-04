#pragma once


#include "chestnut/engine/macros.hpp"
#include "collider2d.hpp"

namespace chestnut::engine
{
    // ============ very simplistics static collision resolution functions, which don't take momentum into account ============ //


    // AFFECTING flag is ignored for the point
    SCollisionResolutionData CHESTNUT_API checkPointVsBox(const CPointCollider2D& point, const CBoxCollider2D& box);

    // AFFECTING flag is ignored for the point
    SCollisionResolutionData CHESTNUT_API checkPointVsCircle(const CPointCollider2D& point, const CCircleCollider2D& circle);

    // Point vs Point collision doesn't happen


    // AFFECTING flag is ignored for the point
    SCollisionResolutionData CHESTNUT_API checkBoxVsPoint(const CBoxCollider2D& box, const CPointCollider2D& point);

    SCollisionResolutionData CHESTNUT_API checkBoxVsBox(const CBoxCollider2D& box1, const CBoxCollider2D& box2);

    SCollisionResolutionData CHESTNUT_API checkBoxVsCircle(const CBoxCollider2D& box, const CCircleCollider2D& circle);
    

    SCollisionResolutionData CHESTNUT_API checkCircleVsPoint(const CCircleCollider2D& circle, const CPointCollider2D& point);

    SCollisionResolutionData CHESTNUT_API checkCircleVsBox(const CCircleCollider2D& circle, const CBoxCollider2D& box);

    SCollisionResolutionData CHESTNUT_API checkCircleVsCircle(const CCircleCollider2D& circle1, const CCircleCollider2D& circle2);

} // namespace chestnut::engine

