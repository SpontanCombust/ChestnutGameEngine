#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/graphics/renderers/renderer.hpp"
#include "chestnut/engine/maths/vector3.hpp"
#include "chestnut/engine/graphics/opengl/buffer.hpp"
#include "chestnut/engine/graphics/opengl/vertex_array.hpp"
#include "chestnut/engine/graphics/opengl/uniform.hpp"
#include "chestnut/engine/graphics/mesh.hpp"

#include <unordered_map>
#include <vector>

namespace chestnut::engine
{
    class CHESTNUT_API CPlainMeshRenderer : public IRenderer
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

