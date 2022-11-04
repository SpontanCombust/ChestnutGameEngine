#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/mesh_data_resource.hpp"
#include "chestnut/engine/graphics/opengl/buffer.hpp"
#include "chestnut/engine/graphics/material.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector3.hpp"


namespace chestnut::engine
{
    class CHESTNUT_API CMeshResource : public IResource
    {
    public:
        unsigned int m_numVertices, m_numIndices;
        std::shared_ptr<CBuffer> m_vboVertices, m_vboNormals, m_vboUVs;
        std::shared_ptr<CBuffer> m_ibo;
        SMaterial m_material;

    public:
        CMeshResource();

        static tl::expected<std::shared_ptr<CMeshResource>, const char *> loadFromGeometry(
            size_t vertexCount,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs,
            size_t indexCount,
            const unsigned int *indices,
            const SMaterial& material);

        static tl::expected<std::shared_ptr<CMeshResource>, const char *> loadFromMeshData(
            const std::shared_ptr<CMeshDataResource>& meshData, 
            const SMaterial& material);

        // For now it always assumes file contains only one mesh with one material
        static tl::expected<std::shared_ptr<CMeshResource>, const char *> loadFromFile(const char *meshPath);
    };

} // namespace chestnut::engine

