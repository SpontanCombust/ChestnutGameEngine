#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/renderers/plain_mesh_renderer.hpp"
#include "chestnut/engine/graphics/light.hpp"


namespace chestnut::engine
{
    class CHESTNUT_API CPhongRenderer : public CPlainMeshRenderer
    {
    private:
        struct SLightUniform
        {
            CUniform<vec3f> position;
            CUniform<vec3f> direction;

            CUniform<vec3f> ambient;
            CUniform<vec3f> diffuse;
            CUniform<vec3f> specular;

            CUniform<float> constant;
            CUniform<float> linear;
            CUniform<float> quadratic;

            CUniform<float> cutOffInner;
            CUniform<float> cutOffOuter;
        };

        enum class ELightType
        {
            DIRECTIONAL,
            POINT,
            SPOT
        };


    private:
        CUniform<vec3f> m_unifCameraPosition;

        CUniform<int> m_unifMaterialSpecular;
        // CUniform<int> m_unifMaterialNormal;
        CUniform<int> m_unifMaterialShininess;

        unsigned char m_lightCountLimit;
        unsigned char m_lightCount;
        std::vector<SLightUniform> m_vecUnifLights;
        std::vector<CUniform<int>> m_vecUnifLightTypes;
        CUniform<unsigned int> m_unifLightCount;

        CTexture2D m_defaultSpecularTexture;
        // CTexture2D m_defaultNormalTexture;
        CTexture2D m_defaultShininessTexture;

    public:
        CPhongRenderer(unsigned char lightCountLimit = 8);

        unsigned char getLightCount() const;
        unsigned char getLightCountLimit() const;


        void clear() override;

        bool submitLight(const CDirectionalLight& light);
        bool submitLight(const CPointLight& light);
        bool submitLight(const CSpotLight& light);

        void render() override;
        void render( const CFramebuffer& targetFramebuffer ) override;

    private:
        bool setShaderProgram() override;
        bool initBuffers() override;
        void onInit() override;
    };

} // namespace chestnut::engine

