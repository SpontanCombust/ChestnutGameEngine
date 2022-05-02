#ifndef __CHESTNUT_ENGINE_PLAIN_MESH_RENDERER_H__
#define __CHESTNUT_ENGINE_PLAIN_MESH_RENDERER_H__

#include "renderer.hpp"
#include "../../maths/vector3.hpp"
#include "../opengl/buffer.hpp"
#include "../opengl/vertex_array.hpp"
#include "../opengl/uniform.hpp"
#include "../mesh.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    class CPlainMeshRenderer : public IRenderer
    {
    protected:
        struct SInstances
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

    protected:
        CUniform<int> m_unifMaterialDiffuse;

        CTexture2D m_defaultDiffuseTexture;
        
        std::unordered_map<GLuint, SInstances> m_mapMeshIDToInstances;


    public:
        CPlainMeshRenderer() = default;

        void clear() override;

        void submitMesh(const CMesh& mesh, const vec3f& translation, const vec3f& scale = vec3f(1.f) );

        void render() override;
        void render( const CFramebuffer& targetFramebuffer ) override;

    protected:
        bool setShaderProgram() override;
        bool initBuffers() override;
        void onInit() override;

        void initInstancesForMesh(const CMesh& mesh);
        void prepareBuffers();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_PLAIN_MESH_RENDERER_H__