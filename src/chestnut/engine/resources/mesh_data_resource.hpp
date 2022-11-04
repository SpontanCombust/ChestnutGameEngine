#pragma once


#include "chestnut/engine/macros.hpp"
#include "resource.hpp"
#include "../maths/vector2.hpp"
#include "../maths/vector3.hpp"

#include <tl/expected.hpp>


namespace chestnut::engine
{
    class CHESTNUT_API CMeshDataResource : public IResource
    {
    public:
        size_t m_numVertices;
        size_t m_numIndices;

        vec3f *m_vertices;
        vec3f *m_normals;
        vec2f *m_uvs;
        unsigned int *m_indices;

    public:
        CMeshDataResource() noexcept;
        ~CMeshDataResource() noexcept;

        // normals, uvs and indices will be given default values
        static tl::expected<std::shared_ptr<CMeshDataResource>, const char *> loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices);

        // normals and uvs will be given default values
        static tl::expected<std::shared_ptr<CMeshDataResource>, const char *> loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices,
            size_t numIndices,
            const unsigned int *indices);

        // indices will be given default values
        static tl::expected<std::shared_ptr<CMeshDataResource>, const char *> loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs);

        static tl::expected<std::shared_ptr<CMeshDataResource>, const char *> loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs,
            size_t numIndices,
            const unsigned int *indices);
    };

} // namespace chestnut::engine

