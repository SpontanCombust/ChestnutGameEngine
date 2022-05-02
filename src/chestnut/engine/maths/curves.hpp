#ifndef __CHESTNUT_ENGINE_CURVES_H__
#define __CHESTNUT_ENGINE_CURVES_H__

#include "vector3.hpp"

#include <vector>


namespace chestnut::engine
{
    struct SBezierCurvePoint
    {
        vec3f position;
        float ratio;
    };

    // All elements besides the first and last are treated as control points
    std::vector<vec3f> plotBezierCurve(const std::vector<SBezierCurvePoint>& points, unsigned int segmentCount);

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_CURVES_H__