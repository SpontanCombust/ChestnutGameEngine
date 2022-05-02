#include "phong_renderer.hpp"

#include "../../resources/resource_manager.hpp"
#include "../../macros.hpp"
#include "../../debug/log.hpp"

namespace chestnut::engine
{    
    static const uint8_t defaultSpecularTextureBytes[] = 
    {
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,   0x00, 0x00, 0x00,
    };
    // static const uint8_t defaultNormalTextureBytes[] = 
    // {
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    //     0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,   0x80, 0x80, 0xff,
    // };
    static const uint8_t defaultShininessTextureBytes[] = 
    {
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
        0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,   0x01,
    };






    CPhongRenderer::CPhongRenderer(unsigned char lightCountLimit)
    : m_lightCountLimit(lightCountLimit), m_lightCount(0)
    {
        m_vecUnifLights.resize(m_lightCountLimit);
        m_vecUnifLightTypes.resize(m_lightCountLimit);
    }

    unsigned char CPhongRenderer::getLightCountLimit() const
    {
        return m_lightCountLimit;
    }

    unsigned char CPhongRenderer::getLightCount() const
    {
        return m_lightCount;
    }





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
        //TODO redo renderer initialization using tl::expected
        CPlainMeshRenderer::initBuffers();


        if(auto uniform = m_shader.getUniform<vec3f>("uCameraPosition")) {
            m_unifCameraPosition = *uniform;
            m_unifCameraPosition = vec3f(0.f);
        } else {
            LOG_WARNING("Diffuse texture uniform not found");
        }


        if(auto uniform = m_shader.getUniform<int>("uMaterial.specular")) {
            m_unifMaterialSpecular = *uniform;
            m_unifMaterialSpecular.set(1);
        } else {
            LOG_WARNING("Specular texture uniform not found");
        }

        if(auto uniform = m_shader.getUniform<int>("uMaterial.shininess")) {
            m_unifMaterialShininess = *uniform;
            m_unifMaterialShininess.set(2);
        } else {
            LOG_WARNING("Normal texture uniform not found");
        }


        if(auto uniform = m_shader.getUniform<unsigned int>("uLightCount")) {
            m_unifLightCount = *uniform;
            m_unifLightCount.set(0);
        } else {
            LOG_WARNING("Normal texture uniform not found");
        }

        bool shouldBreak;
        std::string unifName;
        for (unsigned int i = 0; i < m_lightCountLimit; i++)
        {
            shouldBreak = false;


            unifName = "uLightTypes[" + std::to_string(i) + "]";
            if(auto uniform = m_shader.getUniform<int>(unifName.c_str())) {
                m_vecUnifLightTypes[i] = *uniform;
                m_vecUnifLightTypes[i].set(0);
            } else {
                LOG_WARNING("Light type uniform not found");
                shouldBreak = true;
            }


            unifName = "uLights[" + std::to_string(i) + "].position";
            if(auto uniform = m_shader.getUniform<vec3f>(unifName.c_str()) ) {
                m_vecUnifLights[i].position = *uniform;
            } else {
                LOG_WARNING("Light position uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].direction";
            if(auto uniform = m_shader.getUniform<vec3f>(unifName.c_str()) ) {
                m_vecUnifLights[i].direction = *uniform;
            } else {
                LOG_WARNING("Light direction uniform not found");
                shouldBreak = true;
            }


            unifName = "uLights[" + std::to_string(i) + "].ambient";
            if(auto uniform = m_shader.getUniform<vec3f>(unifName.c_str()) ) {
                m_vecUnifLights[i].ambient = *uniform;
            } else {
                LOG_WARNING("Light ambient uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].diffuse";
            if(auto uniform = m_shader.getUniform<vec3f>(unifName.c_str()) ) {
                m_vecUnifLights[i].diffuse = *uniform;
            } else {
                LOG_WARNING("Light diffuse uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].specular";
            if(auto uniform = m_shader.getUniform<vec3f>(unifName.c_str()) ) {
                m_vecUnifLights[i].specular = *uniform;
            } else {
                LOG_WARNING("Light specular uniform not found");
                shouldBreak = true;
            }


            unifName = "uLights[" + std::to_string(i) + "].constant";
            if(auto uniform = m_shader.getUniform<float>(unifName.c_str()) ) {
                m_vecUnifLights[i].constant = *uniform;
            } else {
                LOG_WARNING("Light constant uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].linear";
            if(auto uniform = m_shader.getUniform<float>(unifName.c_str()) ) {
                m_vecUnifLights[i].linear = *uniform;
            } else {
                LOG_WARNING("Light linear uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].quadratic";
            if(auto uniform = m_shader.getUniform<float>(unifName.c_str()) ) {
                m_vecUnifLights[i].quadratic = *uniform;
            } else {
                LOG_WARNING("Light quadratic uniform not found");
                shouldBreak = true;
            }


            unifName = "uLights[" + std::to_string(i) + "].cutOffInner";
            if(auto uniform = m_shader.getUniform<float>(unifName.c_str()) ) {
                m_vecUnifLights[i].cutOffInner = *uniform;
            } else {
                LOG_WARNING("Light cutOffInner uniform not found");
                shouldBreak = true;
            }

            unifName = "uLights[" + std::to_string(i) + "].cutOffOuter";
            if(auto uniform = m_shader.getUniform<float>(unifName.c_str()) ) {
                m_vecUnifLights[i].cutOffOuter = *uniform;
            } else {
                LOG_WARNING("Light cutOffOuter uniform not found");
                shouldBreak = true;
            }


            if(shouldBreak) {
                if(i > 0) {
                    LOG_WARNING("Light limit higher than the shader can handle. Only " + std::to_string(i) + " lights will be used");
                    m_lightCountLimit = i;
                    m_vecUnifLights.resize(m_lightCountLimit);
                }
                break;
            }
        }

        return true;
    }

    void CPhongRenderer::onInit()
    {
        CPlainMeshRenderer::onInit();

        m_defaultSpecularTexture = CTexture2D(*CTexture2DResource::loadFromPixels(defaultSpecularTextureBytes, 8, 8, 3));
        // m_defaultNormalTexture = CTexture2D(*CTexture2DResource::loadFromImageData(defaultNormalTextureBytes, 8, 8, 3));
        m_defaultShininessTexture = CTexture2D(*CTexture2DResource::loadFromPixels(defaultShininessTextureBytes, 8, 8, 1));

        m_defaultSpecularTexture.setFiltering(GL_NEAREST, GL_NEAREST);
        // m_defaultNormalTexture.setFiltering(GL_NEAREST, GL_NEAREST);
        m_defaultShininessTexture.setFiltering(GL_NEAREST, GL_NEAREST);
    }




    void CPhongRenderer::clear()
    {
        CPlainMeshRenderer::clear();
        m_lightCount = 0;
    }

    bool CPhongRenderer::submitLight(const CDirectionalLight& light)
    {
        if(m_lightCount >= m_lightCountLimit)
        {
            LOG_WARNING("Light limit of " + std::to_string(m_lightCountLimit) + " reached. Light not added");
            return false;
        }

        m_vecUnifLights[m_lightCount].direction = light.m_direction;

        m_vecUnifLights[m_lightCount].ambient = light.m_ambient;
        m_vecUnifLights[m_lightCount].diffuse = light.m_diffuse;
        m_vecUnifLights[m_lightCount].specular = light.m_specular;        

        m_vecUnifLightTypes[m_lightCount] = static_cast<int>(ELightType::DIRECTIONAL);

        m_lightCount++;
        return true;
    }

    bool CPhongRenderer::submitLight(const CPointLight& light)
    {
        if(m_lightCount >= m_lightCountLimit)
        {
            LOG_WARNING("Light limit of " + std::to_string(m_lightCountLimit) + " reached. Light not added");
            return false;
        }

        m_vecUnifLights[m_lightCount].position = light.m_position;

        m_vecUnifLights[m_lightCount].ambient = light.m_ambient;
        m_vecUnifLights[m_lightCount].diffuse = light.m_diffuse;
        m_vecUnifLights[m_lightCount].specular = light.m_specular;

        m_vecUnifLights[m_lightCount].constant = light.m_constant;
        m_vecUnifLights[m_lightCount].linear = light.m_linear;
        m_vecUnifLights[m_lightCount].quadratic = light.m_quadratic;


        m_vecUnifLightTypes[m_lightCount] = static_cast<int>(ELightType::POINT);

        m_lightCount++;
        return true;
    }

    bool CPhongRenderer::submitLight(const CSpotLight& light)
    {
        if(m_lightCount >= m_lightCountLimit)
        {
            LOG_WARNING("Light limit of " + std::to_string(m_lightCountLimit) + " reached. Light not added");
            return false;
        }

        m_vecUnifLights[m_lightCount].position = light.m_position;
        m_vecUnifLights[m_lightCount].direction = light.m_direction;

        m_vecUnifLights[m_lightCount].ambient = light.m_ambient;
        m_vecUnifLights[m_lightCount].diffuse = light.m_diffuse;
        m_vecUnifLights[m_lightCount].specular = light.m_specular;

        m_vecUnifLights[m_lightCount].constant = light.m_constant;
        m_vecUnifLights[m_lightCount].linear = light.m_linear;
        m_vecUnifLights[m_lightCount].quadratic = light.m_quadratic;
        
        m_vecUnifLights[m_lightCount].cutOffInner = light.m_cutoffInner;
        m_vecUnifLights[m_lightCount].cutOffOuter = light.m_cutoffOuter;


        m_vecUnifLightTypes[m_lightCount] = static_cast<int>(ELightType::SPOT);

        m_lightCount++;
        return true;
    }


    


    void CPhongRenderer::render()
    {
        prepareBuffers();

        m_shader.bind();

        // m_unifCameraPosition = m_came
        m_unifLightCount = m_lightCount;

        for(auto& [id, instances] : m_mapMeshIDToInstances)
        {
            glActiveTexture(GL_TEXTURE0);
            if(instances.mesh.getResource()->m_material.diffuse.isValid()) {
                instances.mesh.getResource()->m_material.diffuse.bind();
            } else {
                m_defaultDiffuseTexture.bind();
            }

            glActiveTexture(GL_TEXTURE1);
            if(instances.mesh.getResource()->m_material.specular.isValid()) {
                instances.mesh.getResource()->m_material.specular.bind();
            } else {
                m_defaultSpecularTexture.bind();
            }

            glActiveTexture(GL_TEXTURE2);
            if(instances.mesh.getResource()->m_material.shininess.isValid()) {
                instances.mesh.getResource()->m_material.shininess.bind();
            } else {
                m_defaultShininessTexture.bind();
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

    void CPhongRenderer::render(const CFramebuffer& targetFramebuffer)
    {
        targetFramebuffer.bind();
        render();
        targetFramebuffer.unbind();
    }
}