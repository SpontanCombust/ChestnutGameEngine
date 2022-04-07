#include "phong_renderer.hpp"

#include "../../resources/resource_manager.hpp"
#include "../../macros.hpp"
#include "../../debug/log.hpp"

namespace chestnut::engine
{    
    bool CPhongRenderer::setShaderProgram()
    {
        auto shader = CResourceManager::getOrLoadResource<CShaderProgramResource>(
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/phong.vert", 
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/phong.frag"
        );

        if(shader) {
            m_shader = CShaderProgram(*shader);
        } else {
            LOG_ERROR(shader.error());
            return false;
        }

        return true;
    }

    bool CPhongRenderer::initBuffers()
    {
        // buffers will be crated when new meshes will be submitted

        //TODO redo renderer initialization using tl::expected
        m_unifMaterialDiffuse = m_shader.getUniform<int>("uMaterial.diffuse").value();
        m_unifMaterialDiffuse.set(0);

        return true;
    }




    void CPhongRenderer::clear()
    {
        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            instances.vecTransforms.clear();
        }
    }

    void CPhongRenderer::submitMesh(const CMesh& mesh, const vec3f& translation, const vec3f& scale)
    {
        if(m_mapMeshIDToInstances.find(mesh.getResource()->m_vboVertices->getID()) == m_mapMeshIDToInstances.end())
        {
            initInstancesForMesh(mesh);
        }

        m_mapMeshIDToInstances[mesh.getResource()->m_vboVertices->getID()].vecTransforms.push_back({translation, scale});
    }

    


    void CPhongRenderer::initInstancesForMesh(const CMesh& mesh)
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

    void CPhongRenderer::prepareBuffers()
    {
        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            instances.vboInstance->update(
                instances.vecTransforms.data(),
                instances.vecTransforms.size() * sizeof(instances.vecTransforms[0])
            );
        }
    }

    void CPhongRenderer::render()
    {
        prepareBuffers();

        m_shader.bind();

        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            glActiveTexture(GL_TEXTURE0);
            //TODO if mesh doesn't have some material textures, assign default textures
            glBindTexture(GL_TEXTURE_2D, instances.mesh.getResource()->m_material.diffuse->m_texID);            

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

    void CPhongRenderer::render(const CFramebuffer& targetFramebuffer)
    {
        targetFramebuffer.bind();
        render();
        targetFramebuffer.unbind();
    }
}