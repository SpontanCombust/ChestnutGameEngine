#include "chestnut/engine_extensions/graphics3d/resources/mesh_data_resource.hpp"

#include <cstring>


namespace chestnut::engine
{    
    CMeshDataResource::CMeshDataResource() noexcept
    : m_numVertices(0),
      m_numIndices(0),
      m_vertices(nullptr),
      m_normals(nullptr),
      m_uvs(nullptr),
      m_indices(nullptr)
    {

    }

    CMeshDataResource::~CMeshDataResource() noexcept
    {
        delete[] m_vertices;   
        delete[] m_normals;   
        delete[] m_uvs;   
        delete[] m_indices;
    }



    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> CMeshDataResource::loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices)
    {
        if(numVertices == 0) {
            return tl::make_unexpected("numVertices must be greater than 0");
        } else if(!vertices) {
            return tl::make_unexpected("vertices must not be null");
        }


        auto resource = std::make_shared<CMeshDataResource>();

        resource->m_numVertices = numVertices;
        resource->m_vertices = new vec3f[numVertices];
        std::memcpy(resource->m_vertices, vertices, sizeof(vec3f) * numVertices);

        resource->m_normals = new vec3f[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_normals[i] = vec3f(1.0f, 0.0f, 0.0f);
        }
        
        resource->m_uvs = new vec2f[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_uvs[i] = vec2f(0.0f, 0.0f);
        }

        resource->m_numIndices = numVertices;
        resource->m_indices = new unsigned int[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_indices[i] = i;
        }

        return resource;
    }


    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> CMeshDataResource::loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices,
            size_t numIndices,
            const unsigned int *indices)
    {
        if(numVertices == 0) {
            return tl::make_unexpected("numVertices must be greater than 0");
        } else if(!vertices) {
            return tl::make_unexpected("vertices must not be null");
        } else if(numIndices == 0) {
            return tl::make_unexpected("numIndices must be greater than 0");
        } else if(!indices) {
            return tl::make_unexpected("indices must not be null");
        }


        auto resource = std::make_shared<CMeshDataResource>();

        resource->m_numVertices = numVertices;
        resource->m_vertices = new vec3f[numVertices];
        std::memcpy(resource->m_vertices, vertices, sizeof(vec3f) * numVertices);

        resource->m_normals = new vec3f[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_normals[i] = vec3f(1.0f, 0.0f, 0.0f);
        }
        
        resource->m_uvs = new vec2f[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_uvs[i] = vec2f(0.0f, 0.0f);
        }

        resource->m_numIndices = numIndices;
        resource->m_indices = new unsigned int[numVertices];
        std::memcpy(resource->m_indices, indices, sizeof(unsigned int) * numIndices);

        return resource;
    }


    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> loadFromGeometry(
            size_t numVertices,
            const vec3f *vertices,
            const vec3f *normals,
            const vec2f *uvs)
    {
        if(numVertices == 0) {
            return tl::make_unexpected("numVertices must be greater than 0");
        } else if(!vertices) {
            return tl::make_unexpected("vertices must not be null");
        } else if(!normals) {
            return tl::make_unexpected("normals must not be null");
        } else if(!uvs) {
            return tl::make_unexpected("uvs must not be null");
        }


        auto resource = std::make_shared<CMeshDataResource>();

        resource->m_numVertices = numVertices;
        resource->m_vertices = new vec3f[numVertices];
        std::memcpy(resource->m_vertices, vertices, sizeof(vec3f) * numVertices);

        resource->m_normals = new vec3f[numVertices];
        std::memcpy(resource->m_normals, normals, sizeof(vec3f) * numVertices);
        
        resource->m_uvs = new vec2f[numVertices];
        std::memcpy(resource->m_uvs, uvs, sizeof(vec2f) * numVertices);

        resource->m_numIndices = numVertices;
        resource->m_indices = new unsigned int[numVertices];
        for (size_t i = 0; i < numVertices; i++)
        {
            resource->m_indices[i] = i;
        }

        return resource;
    }


    tl::expected<std::shared_ptr<CMeshDataResource>, const char *> CMeshDataResource::loadFromGeometry(
        size_t numVertices,
        const vec3f *vertices,
        const vec3f *normals,
        const vec2f *uvs,
        size_t numIndices,
        const unsigned int *indices)
    {
        if(numVertices == 0) {
            return tl::make_unexpected("numVertices must be greater than 0");
        } else if(!vertices) {
            return tl::make_unexpected("vertices must not be nullptr");
        } else if(!normals) {
            return tl::make_unexpected("normals must not be null");
        } else if(!uvs) {
            return tl::make_unexpected("uvs must not be null");
        } else if(numIndices == 0) {
            return tl::make_unexpected("numIndices must be greater than 0");
        } else if(!indices) {
            return tl::make_unexpected("indices must not be null");
        }


        auto resource = std::make_shared<CMeshDataResource>();

        resource->m_numVertices = numVertices;
        resource->m_vertices = new vec3f[numVertices];
        std::memcpy(resource->m_vertices, vertices, sizeof(vec3f) * numVertices);

        resource->m_normals = new vec3f[numVertices];
        std::memcpy(resource->m_normals, normals, sizeof(vec3f) * numVertices);

        resource->m_uvs = new vec2f[numVertices];
        std::memcpy(resource->m_uvs, uvs, sizeof(vec2f) * numVertices);
        
        resource->m_numIndices = numIndices;
        resource->m_indices = new unsigned int[numIndices];
        std::memcpy(resource->m_indices, indices, sizeof(unsigned int) * numIndices);

        return resource; 
    }
} // namespace chestnut::engine
