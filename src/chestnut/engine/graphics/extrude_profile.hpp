#ifndef __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__
#define __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__

#include "../resources/mesh_resource.hpp"
#include "../maths/vector3.hpp"

namespace chestnut::engine
{
    struct SExtrusionPoint
    {
        vec3f position;
        vec3f direction;
        float roll;
    };

    tl::expected<std::shared_ptr<CMeshResource>, const char *> extrudeProfile(std::vector<vec2f> profile, const std::vector<SExtrusionPoint>& extrusionPoints);

} // namespace chestnut::engine


#endif // __CHESTNUT_ENGINE_EXTRUDE_PROFILE_H__