#ifndef __CHESTNUT_ENGINE_PHONG_RENDERER_H__
#define __CHESTNUT_ENGINE_PHONG_RENDERER_H__

#include "renderer.hpp"
#include "../opengl/buffer.hpp"
#include "../opengl/vertex_array.hpp"
#include "../opengl/uniform.hpp"
#include "../mesh.hpp"
#include "../../maths/vector3.hpp"
#include "../light.hpp"

#include <unordered_map>
#include <vector>


namespace chestnut::engine
{
    class CPhongRenderer : public IRenderer
    {
    private:
        struct SPhongRender_Instances
        {
            struct STransform
            {
                vec3f translation;
                vec3f scale;
            };

            CMesh mesh;
            CVertexArray vao;
            std::shared_ptr<CBuffer> vboInstance;

            std::vector<STransform> vecTransforms; // also says how many intances there are
        };

        struct SMaterialUniform
        {
            CUniform<int> diffuse;
            CUniform<int> specular;
            CUniform<int> shininess;
        };

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

        SMaterialUniform m_unifMaterial;

        unsigned char m_lightCountLimit;
        unsigned char m_lightCount;
        std::vector<SLightUniform> m_vecUnifLights;
        std::vector<CUniform<int>> m_vecUnifLightTypes;
        CUniform<unsigned int> m_unifLightCount;

        CTexture2D m_defaultDiffuseTexture;
        CTexture2D m_defaultSpecularTexture;
        // CTexture2D m_defaultNormalTexture;
        CTexture2D m_defaultShininessTexture;

        std::unordered_map<GLuint, SPhongRender_Instances> m_mapMeshIDToInstances;


    public:
        CPhongRenderer(unsigned char lightCountLimit = 8);

        unsigned char getLightCount() const;
        unsigned char getLightCountLimit() const;


        void clear() override;

        void submitMesh(const CMesh& mesh, const vec3f& translation, const vec3f& scale = vec3f(1.f) );
        bool submitLight(const CDirectionalLight& light);
        bool submitLight(const CPointLight& light);
        bool submitLight(const CSpotLight& light);

        void render() override;
        void render( const CFramebuffer& targetFramebuffer ) override;

    private:
        bool setShaderProgram() override;
        bool initBuffers() override;
        void onInit() override;

        void initInstancesForMesh(const CMesh& mesh);
        void prepareBuffers();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_PHONG_RENDERER_H__