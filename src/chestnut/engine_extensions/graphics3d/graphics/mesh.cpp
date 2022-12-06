#include "chestnut/engine_extensions/graphics3d/graphics/mesh.hpp"

#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
{
    CMesh::CMesh()
    {
    }

    CMesh::CMesh(std::shared_ptr<CMeshResource> resource)
        : m_resource(resource)
    {
    }

    CMesh::CMesh(std::shared_ptr<CMeshDataResource> resource, const SMaterial& material) 
    {
        auto meshResource = CMeshResource::loadFromMeshData(resource, material);
        if(meshResource) {
            m_resource = *meshResource;
        } else {
            LOG_ERROR("Failed to load mesh resource from mesh data resource");
            m_resource = nullptr;
        }

    }

    bool CMesh::isValid() const
    {
        return m_resource != nullptr;
    }

    const std::shared_ptr<CMeshResource>& CMesh::getResource() const
    {
        return m_resource;
    }

    tl::optional<const char *> CMesh::addBuffersToVAO(CVertexArray& vao, const CShaderProgram& shaderProgram, 
                const char *vertPosAttribName, 
                const char *vertNormalAttribName, 
                const char *vertUVAttribName) const
    {
        if(!shaderProgram.isValid())
        {
            return "Shader program is not valid";
        }

        vao.addBuffer(m_resource->m_ibo);

        if(auto attrib = shaderProgram.getAttribute<vec3f>(vertPosAttribName, false)) {
            vao.addBuffer(m_resource->m_vboVertices, {*attrib});
        } else {
            return "Could not find vertex position attribute";
        }

        if(auto attrib = shaderProgram.getAttribute<vec2f>(vertUVAttribName, false)) {
            vao.addBuffer(m_resource->m_vboUVs, {*attrib});
        } else {
            return "Could not find vertex uv attribute";
        }

        if(auto attrib = shaderProgram.getAttribute<vec3f>(vertNormalAttribName, false)) {
            vao.addBuffer(m_resource->m_vboNormals, {*attrib});
        } else {
            return "Could not find vertex normal attribute";
        } 

        return tl::nullopt;
    }

} // namespace chestnut::engine
