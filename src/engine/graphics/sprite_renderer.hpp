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
        struct SSpriteInstance
        {
            vec2f origin;
            vec2f transl;
            vec2f scale;
            float rot;
            vec4f clipRect;
        };

        struct SSpriteBatch
        {
            GLuint texID;
            GLsizei instanceAmount;
            GLuint instanceOffset;
        };
        
    private:
        std::unordered_map< GLuint, std::vector< SSpriteInstance > > m_mapTexIDToVecInstances;
        std::unordered_map< GLuint, vec2f > m_mapTexIDToSize;
        std::vector< SSpriteBatch > m_vecBatches;

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

        void submitSprite( const CTexture2D& texture, const vec2f& origin, const vec2f& position, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );
        // requires bound renderer shader
        void render();

    private:
        bool setShaderVariableNames( const std::string& attrVertPos,
                                     const std::string& attrVertUVPos,
                                     const std::string& attrInstOrigin,
                                     const std::string& attrInstTransl,
                                     const std::string& attrInstScale,
                                     const std::string& attrInstRot,
                                     const std::string& attrInstUVTransl,
                                     const std::string& attrInstUVScale,
                                     const std::string& unifView,
                                     const std::string& unifProjection );

        void initBuffers();

        void makeBatches();
    };

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_H__