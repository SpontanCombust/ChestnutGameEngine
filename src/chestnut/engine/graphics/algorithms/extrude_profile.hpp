#ifndef __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__
#define __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__

#include "chestnut/engine/macros.hpp"
#include "../../resources/mesh_data_resource.hpp"
#include "../../maths/vector3.hpp"
#include "../../maths/curves.hpp"


namespace chestnut::engine
{
    struct SExtrusionPoint
    {
        vec3f position;
        vec3f direction;
        float roll;
    };

    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> 
    CHESTNUT_API 
    extrudeProfile(std::vector<vec2f> profile, const std::vector<SExtrusionPoint>& extrusionPoints);

    // All elements besides the first and last in curvePoints are treated as control points
    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> 
    CHESTNUT_API 
    extrudeProfileWithCurve(std::vector<vec2f> profile, const std::vector<SBezierCurvePoint>& curvePoints, unsigned int segmentCount);

} // namespace chestnut::engine


#endif // __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__