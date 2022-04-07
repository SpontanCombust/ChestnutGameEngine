#ifndef __CHESTNUT_ENGINE_PHONG_RENDERER_H__
#define __CHESTNUT_ENGINE_PHONG_RENDERER_H__

#include "renderer.hpp"
#include "../opengl/buffer.hpp"
#include "../opengl/vertex_array.hpp"
#include "../opengl/uniform.hpp"
#include "../mesh.hpp"
#include "../../maths/vector3.hpp"

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

        CUniform<int> m_unifMaterialDiffuse;
        CUniform<int> m_unifMaterialSpecular;
        CUniform<int> m_unifMaterialNormal;

        CTexture2D m_defaultDiffuseTexture;
        CTexture2D m_defaultSpecularTexture;
        CTexture2D m_defaultNormalTexture;

        std::unordered_map<GLuint, SPhongRender_Instances> m_mapMeshIDToInstances;


    public:
        void clear() override;

        void submitMesh(const CMesh& mesh, const vec3f& translation, const vec3f& scale = vec3f(1.f) );

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