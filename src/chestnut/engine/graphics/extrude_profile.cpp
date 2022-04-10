#include "extrude_profile.hpp"

#include "../maths/vector_transform.hpp"

#include <cmath>


namespace chestnut::engine
{
    const vec3f INIT_PROFILE_FORWARD_VECTOR = vec3f(0.f, 1.f, 0.f);

    tl::expected<std::shared_ptr<CMeshResource>, const char *> extrudeProfile(std::vector<vec2f> profile, const std::vector<SExtrusionPoint>& extrusionPoints)
    {
        if(extrusionPoints.size() < 2)
        {
            return tl::make_unexpected("extrusionPoints must have at least 2 points");
        }

        // generate vertices
        std::vector<vec3f> vertices;
        for(const auto& ep : extrusionPoints)
        {
            vec3f direction = vecNormalized(ep.direction);
            // the angle of rotation of the direction vector
            float directionAngleDelta = std::acos(vecDotProduct(INIT_PROFILE_FORWARD_VECTOR, direction));
            // the vector around which said direction vector is rotated
            vec3f directionRotationVec;
            // avoid calculating with NaN value
            if(direction == INIT_PROFILE_FORWARD_VECTOR || direction == -INIT_PROFILE_FORWARD_VECTOR)
            {
                directionRotationVec = {0.f, 0.f, 1.f};
            }
            else
            {
                directionRotationVec = vecCrossProduct(INIT_PROFILE_FORWARD_VECTOR, direction);
            }
            
            for(const auto& p : profile)
            {
                // initialize the vertex with profile coords
                vec3f vert = {p.x, 0.f, p.y};
                
                // rotate the vertex by the angle the direction vector makes with base vector of the profile
                vecRotate(vert, directionRotationVec, directionAngleDelta);
                // now rotate the vertex by the roll angle
                vecRotate(vert, direction, ep.roll);
                // move vertex to the position
                vert += ep.position;
                
                vertices.push_back(vert);
            }
        }

        // generate indices
        std::vector<unsigned int> indices;
        for (size_t i = 0; i < extrusionPoints.size() - 1; i++)
        {
            for (size_t j = 0; j < profile.size() - 1; j++)
            {
                indices.push_back(i * profile.size() + j);
                indices.push_back(i * profile.size() + (j + 1));
                indices.push_back((i + 1) * profile.size() + (j + 1));

                indices.push_back(i * profile.size() + j);
                indices.push_back((i + 1) * profile.size() + (j + 1));
                indices.push_back((i + 1) * profile.size() + j);
            }

            indices.push_back(i * profile.size() + profile.size() - 1);
            indices.push_back(i * profile.size() + 0);
            indices.push_back((i + 1) * profile.size() + 0);

            indices.push_back(i * profile.size() + profile.size() - 1);
            indices.push_back((i + 1) * profile.size() + 0);
            indices.push_back((i + 1) * profile.size() + profile.size() - 1);
        }

        // generate uvs
        std::vector<vec2f> uvs;
        for (size_t i = 0; i < extrusionPoints.size(); i++)
        {
            for (size_t j = 0; j < profile.size(); j++)
            {
                uvs.push_back(vec2f(0.f, 0.f));
                uvs.push_back(vec2f(1.f, 0.f));
                uvs.push_back(vec2f(1.f, 1.f));
                
                uvs.push_back(vec2f(0.f, 0.f));
                uvs.push_back(vec2f(1.f, 1.f));
                uvs.push_back(vec2f(0.f, 1.f));
            }
        }

        // for now use only dummy normals
        return CMeshResource::loadFromGeometry(
            vertices.size(),
            vertices.data(),
            vertices.data(),
            uvs.data(),
            indices.size(),
            indices.data(),
            SMaterial{}
        );
    }

} // namespace chestnut::engine
