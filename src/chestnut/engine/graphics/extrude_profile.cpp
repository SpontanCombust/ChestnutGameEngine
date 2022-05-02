#include "extrude_profile.hpp"

#include "../maths/vector_transform.hpp"

#include <cmath> // std::acos


namespace chestnut::engine
{
    const vec3f PROFILE_NORMAL = vec3f(0.f, 0.f, 1.f);

    tl::expected<std::shared_ptr<CMeshResource>, const char *> extrudeProfile(std::vector<vec2f> profile, const std::vector<SExtrusionPoint>& extrusionPoints)
    {
        if(extrusionPoints.size() < 2)
        {
            return tl::make_unexpected("ExtrusionPoints must have at least 2 points");
        }

        // so that indexing is easier and texture wrapping across a segment is possible
        profile.push_back(profile[0]);
        const int profileSize = profile.size();
        

        // ============= VERTICES ============= //
        // each vertex of the profile is being transformed for every extrusion point
        // and added to the `vertices` vector
        std::vector<vec3f> vertices;
        vertices.reserve(profileSize * extrusionPoints.size());
        for(const auto& ep : extrusionPoints)
        {
            vec3f direction = vecNormalized(ep.direction);
            // the angle of rotation of the direction vector
            float rotationAngle = std::acos(vecDotProduct(PROFILE_NORMAL, direction));
            // the vector around which said direction vector is rotated
            vec3f rotationNormal;
            // avoid calculating with NaN value
            if(direction == PROFILE_NORMAL || direction == -PROFILE_NORMAL)
            {
                rotationNormal = {1.f, 0.f, 0.f};
            }
            else
            {
                rotationNormal = vecCrossProduct(PROFILE_NORMAL, direction);
            }
            
            for (int j = 0; j < profileSize - 1; j++)
            {
                // initialize the vertex with profile coords
                vec3f vert = {profile[j].x, profile[j].y, 0.f};
                
                // rotate the vertex by the angle the direction vector makes with base vector of the profile
                vecRotate(vert, rotationNormal, rotationAngle);
                // now rotate the vertex by the roll angle
                vecRotate(vert, direction, ep.roll);
                // move vertex to the position
                vert += ep.position;
                
                vertices.push_back(vert);
            }
            vertices.push_back( *(vertices.end() - (profileSize - 1)) ); // for that one repeated vertex
        }

        
        // ============= UVS ============= //
        std::vector<vec2f> uvs;
        uvs.reserve(profileSize * extrusionPoints.size());
        for (size_t i = 0; i < extrusionPoints.size(); i++)
        {
            // a texture will be wrapped around a single segment and will repeat with every segment
            for (int j = 0; j < profileSize; j++)
            {
                uvs.push_back(vec2f(
                    float(j) / float(profileSize - 1),
                    float(i)
                ));
            }
        }


        // ============= NORMALS ============= //
        // calculate normal based on the faces of the next curve mesh segment
        std::vector<vec3f> normals;
        normals.reserve(profileSize * extrusionPoints.size());
        auto calcNormalAfter = [&](int i, int j) -> vec3f {
            vec3f vThis = vertices[i * profileSize + j];

            vec3f vRight = vertices[i * profileSize + j + 1];
            
            vec3f vUp = vertices[(i + 1) * profileSize + j];
            
            vec3f vLeft;
            if(j > 0) {
                vLeft = vertices[i * profileSize + j - 1];
            } else {
                vLeft = vertices[(i + 1) * profileSize - 2];
            }

            vec3f n1 = vecCrossProduct(vRight - vThis, vUp - vThis);
            vec3f n2 = vecCrossProduct(vUp - vThis, vLeft - vThis);

            return vecNormalized(n1 + n2);
        };

        // calculate normal based on the faces of the previous curve mesh segment
        auto calcNormalBefore = [&](int i, int j) -> vec3f {
            vec3f vThis = vertices[i * profileSize + j];

            vec3f vLeft;
            if(j > 0) {
                vLeft = vertices[i * profileSize + j - 1];
            } else {
                vLeft = vertices[(i + 1) * profileSize - 2];
            }

            vec3f vDown = vertices[(i - 1) * profileSize + j];

            vec3f vRight = vertices[i * profileSize + j + 1];

            vec3f n1 = vecCrossProduct(vLeft - vThis, vDown - vThis);
            vec3f n2 = vecCrossProduct(vDown - vThis, vRight - vThis);

            return vecNormalized(n1 + n2);
        };


        for (size_t j = 0; j < profile.size(); j++)
        {
            normals.push_back(calcNormalAfter(0, j));
        }
        normals.push_back( *(normals.end() - (profileSize - 1)) ); // for that one repeated vertex

        for (size_t i = 1; i < extrusionPoints.size() - 1; i++)
        {
            for (size_t j = 0; j < profile.size() - 1; j++)
            {
                vec3f nBefore = calcNormalBefore(i, j);
                vec3f nAfter = calcNormalAfter(i, j);
                normals.push_back(vecNormalized(nBefore + nAfter));
            }
            normals.push_back( *(normals.end() - (profileSize - 1)) );
        }

        for (size_t j = 0; j < profile.size(); j++)
        {
            normals.push_back(calcNormalBefore(extrusionPoints.size() - 1, j));
        }
        normals.push_back( *(normals.end() - (profileSize - 1)) );


        // ============= INDICES ============= //
        std::vector<unsigned int> indices;
        indices.reserve((extrusionPoints.size() - 1) * (profileSize - 1) * 6);
        for (size_t i = 0; i < extrusionPoints.size() - 1; i++)
        {
            for (int j = 0; j < profileSize - 1; j++)
            {
                indices.push_back(i * profileSize + j);
                indices.push_back(i * profileSize + (j + 1));
                indices.push_back((i + 1) * profileSize + (j + 1));

                indices.push_back(i * profileSize + j);
                indices.push_back((i + 1) * profileSize + (j + 1));
                indices.push_back((i + 1) * profileSize + j);
            }
        }

        
        return CMeshResource::loadFromGeometry(
            vertices.size(),
            vertices.data(),
            normals.data(),
            uvs.data(),
            indices.size(),
            indices.data(),
            SMaterial{}
        );
    }




    tl::expected<std::shared_ptr<CMeshResource>, const char *> extrudeProfileWithCurve(std::vector<vec2f> profile, const std::vector<SBezierCurvePoint>& curvePoints, unsigned int segmentCount)
    {
        auto curve = plotBezierCurve(curvePoints, segmentCount);

        if(curve.size() < 2)
        {
            return tl::make_unexpected("curvePoints must have at least 2 points");
        }

        std::vector<SExtrusionPoint> extrusionPoints(curve.size());

        extrusionPoints.push_back({curve[0], curve[1] - curve[0], 0.f});
        for (size_t i = 1; i < curve.size() - 1; i++)
        {
            extrusionPoints.push_back({curve[i], curve[i + 1] - curve[i - 1], 0.f});
        }
        extrusionPoints.push_back({curve[curve.size() - 1], curve[curve.size() - 1] - curve[curve.size() - 2], 0.f});

        return extrudeProfile(profile, extrusionPoints);
    }

} // namespace chestnut::engine
