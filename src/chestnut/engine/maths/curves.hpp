#pragma once


#include "chestnut/engine/macros.hpp"
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
    std::vector<vec3f> CHESTNUT_API plotBezierCurve(const std::vector<SBezierCurvePoint>& points, unsigned int segmentCount);

} // namespace chestnut::engine

