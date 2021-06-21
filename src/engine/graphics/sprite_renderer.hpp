#ifndef __CHESTNUT_SPRITE_RENDERER_H__
#define __CHESTNUT_SPRITE_RENDERER_H__

#include "engine/libs.hpp"
#include "shader_program.hpp"
#include "texture2d.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/matrix3.hpp"
#include "engine/maths/matrix4.hpp"

#include <vector>
#include <unordered_map>

namespace chestnut
{

    class CSpriteRenderer
    {
        struct SSpriteRender_Instance
        {
            vec2f origin;
            vec2f transl;
            vec2f scale;
            float rot;
            vec4f clipRect;
            vec3f tint;
            float tintFactor;
        };

        struct SSpriteRender_InstanceGroup
        {
            GLuint texID;
            vec2f texSize;
            std::vector< SSpriteRender_Instance > vecInstances;
        };

        struct SSpriteRender_Batch
        {
            GLuint texID;
            vec2f texSize;
            GLsizei instanceAmount;
            GLuint instanceOffset;
        };
        
    private:
        std::unordered_map< GLuint, SSpriteRender_InstanceGroup > m_mapTexIDToInstanceGroup;
        std::vector< SSpriteRender_Batch > m_vecBatches;

        GLuint m_vao;
        GLuint m_vboVert;
        GLuint m_vboInst;
        GLuint m_ebo;
        GLsizei m_spriteCapacity;

        CShaderProgram m_shader;


        GLint m_unifViewLoc;
        GLint m_unifProjectionLoc;

        GLint m_attrVertPosLoc;
        GLint m_attrVertUVPosLoc;

        GLint m_unifTexSizeLoc;

        GLint m_attrInstOriginLoc;
        GLint m_attrInstTranslLoc;
        GLint m_attrInstScaleLoc;
        GLint m_attrInstRotLoc;
        GLint m_attrInstClipRectLoc;
        GLint m_attrInstTint;
        GLint m_attrInstTintFactor;


    public:
        CSpriteRenderer( const CShaderProgram& shader );
        ~CSpriteRenderer();

        void bindShader();
        void unbindShader();
        
        // requires bound renderer shader
        void setProjectionMatrix( const mat4f& mat );
        // requires bound renderer shader
        void setViewMatrix( const mat4f& mat );
        // requires bound renderer shader
        void reserveBufferSpace( GLsizei targetSpriteCapacity );

        void clear();

        void submitSprite( const CTexture2D& texture, const vec2f& position, const vec2f& origin = { 0.f, 0.f }, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );
        // requires bound renderer shader
        void render();

    private:
        bool setShaderVariableNames( const std::string& attrVertPos,
                                     const std::string& attrVertUVPos,
                                     const std::string& attrInstOrigin,
                                     const std::string& attrInstTransl,
                                     const std::string& attrInstScale,
                                     const std::string& attrInstRot,
                                     const std::string& attrInstClipRect,
                                     const std::string& attrInstTint,
                                     const std::string& attrInstTintFactor,
                                     const std::string& unifTexSize,
                                     const std::string& unifView,
                                     const std::string& unifProjection );

        void initBuffers();

        void makeBatches();
    };

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_H__