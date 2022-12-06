#include "chestnut/engine_extensions/graphics3d/graphics/renderers/plain_mesh_renderer.hpp"

#include "chestnut/engine/resources/resource_manager.hpp"
#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/debug/log.hpp"

namespace chestnut::engine
{    
    static const uint8_t defaultDiffuseTextureBytes[] = 
    {
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
    };



    bool CPlainMeshRenderer::setShaderProgram()
    {
        auto shader = CResourceManager::getOrLoadResource<CShaderProgramResource>(
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/plain_mesh.vert", 
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/plain_mesh.frag"
        );

        if(shader) {
            m_shader = CShaderProgram(*shader);
        } else {
            LOG_ERROR(shader.error());
            return false;
        }

        return true;
    }

    bool CPlainMeshRenderer::initBuffers()
    {
        // buffers will be crated when new meshes will be submitted

        if(auto uniform = m_shader.getUniform<int>("uMaterial.diffuse")) {
            m_unifMaterialDiffuse = *uniform;
            m_unifMaterialDiffuse.set(0);
        } else {
            LOG_WARNING("Diffuse texture uniform not found");
        }

        return true;
    }

    void CPlainMeshRenderer::onInit()
    {
        m_defaultDiffuseTexture = CTexture2D(*CTexture2DResource::loadFromPixels(defaultDiffuseTextureBytes, 8, 8, 3));
        m_defaultDiffuseTexture.setFiltering(GL_NEAREST, GL_NEAREST);
    }

    void CPlainMeshRenderer::initInstancesForMesh(const CMesh& mesh)
    {
        auto& instances = m_mapMeshIDToInstances[mesh.getResource()->m_vboVertices->getID()];

        instances.mesh = mesh;
        instances.vboInstance = std::make_shared<CBuffer>(
            CBuffer::EType::VERTEX,
            CBuffer::EUsage::DYNAMIC_DRAW,
            CBuffer::ELayout::ARRAY_OF_STRUCTS
        );

        if( auto err = mesh.addBuffersToVAO(instances.vao, m_shader, "avPos", "avNormal", "avUV")) {
            LOG_ERROR(err.value());
            // return;
        }
        instances.vao.addBuffer(instances.vboInstance, {
            m_shader.getAttribute<vec3f>("aiTranslation", true).value(),
            m_shader.getAttribute<vec3f>("aiScale", true).value()
        });

        instances.vao.compose();
    }

    void CPlainMeshRenderer::clear()
    {
        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            instances.vecTransforms.clear();
        }
    }

    void CPlainMeshRenderer::submitMesh(const CMesh& mesh, const vec3f& translation, const vec3f& scale)
    {
        if(m_mapMeshIDToInstances.find(mesh.getResource()->m_vboVertices->getID()) == m_mapMeshIDToInstances.end())
        {
            initInstancesForMesh(mesh);
        }

        m_mapMeshIDToInstances[mesh.getResource()->m_vboVertices->getID()].vecTransforms.push_back({translation, scale});
    }

    void CPlainMeshRenderer::prepareBuffers()
    {
        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            instances.vboInstance->update(
                instances.vecTransforms.data(),
                instances.vecTransforms.size() * sizeof(instances.vecTransforms[0])
            );
        }
    }

    void CPlainMeshRenderer::render()
    {
        prepareBuffers();

        m_shader.bind();

        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            glActiveTexture(GL_TEXTURE0);
            if(instances.mesh.getResource()->m_material.diffuse.isValid()) {
                instances.mesh.getResource()->m_material.diffuse.bind();
            } else {
                m_defaultDiffuseTexture.bind();
            }

            instances.vao.bind();
                glDrawElementsInstanced(
                    GL_TRIANGLES, 
                    instances.mesh.getResource()->m_numIndices, 
                    GL_UNSIGNED_INT, 
                    nullptr, 
                    instances.vecTransforms.size()
                );
            instances.vao.unbind();
        }
    }

    void CPlainMeshRenderer::render(const CFramebuffer& targetFramebuffer)
    {
        targetFramebuffer.bind();
        render();
        targetFramebuffer.unbind();
    }

} // namespace chestnut::engine
