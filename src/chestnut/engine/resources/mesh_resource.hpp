#ifndef __CHESTNUT_ENGINE_MESH_RESOURCE_H__
#define __CHESTNUT_ENGINE_MESH_RESOURCE_H__

#include "resource.hpp"
#include "../graphics/opengl/buffer.hpp"
#include "../graphics/material.hpp"
#include "../maths/vector2.hpp"
#include "../maths/vector3.hpp"

#include <tl/optional.hpp>


namespace chestnut::engine
{
    class CMeshResource : public IResource
    {
    public:
        unsigned int m_numVertices, m_numIndices;
        std::shared_ptr<CBuffer> m_vboVertices, m_vboNormals, m_vboUVs;
        std::shared_ptr<CBuffer> m_ibo;
        SMaterial m_material;

    public:
        CMeshResource();

        static std::shared_ptr<CMeshResource> loadFromGeometry(
            unsigned int vertexCount,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs,
            unsigned int indexCount,
            const unsigned int *indices,
            const SMaterial& material
        );

        // For now it always assumes file contains only one mesh with one material
        static tl::expected<std::shared_ptr<CMeshResource>, const char *> loadFromFile(const char *meshPath);
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_MESH_RESOURCE_H__