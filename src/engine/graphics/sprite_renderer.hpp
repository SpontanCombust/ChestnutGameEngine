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
        struct STexturedVertex
        {
            vec2f pos;
            vec2f uv; 
        };

        struct SSpriteBatch
        {
            GLuint texID;
            int elementAmount;
            size_t elementOffset;
        };
        
    private:
        std::unordered_map< GLuint, std::vector< STexturedVertex > > m_mapTexIDToVecVertices;
        std::vector< SSpriteBatch > m_vecBatches;

        GLuint m_vao;
        GLuint m_vbo;
        GLuint m_ebo;
        GLsizei m_spriteCapacity;

        CShaderProgram m_shader;

        GLint m_attrPosLoc;
        GLint m_attrUVLoc;

        GLint m_unifViewLoc;
        GLint m_unifProjectionLoc;

        STexturedVertex m_lookupBaseVertices[4];

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

        void submitSprite( const CTexture2D& texture, const vec2f& position, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );
        // requires bound renderer shader
        void render();

    private:
        bool setShaderVariableNames( const std::string& attrPos, 
                                     const std::string& attrTexCoord, 
                                     const std::string& unifView,
                                     const std::string& unifProjection );

        void initBuffers();

        void initLookupVertices();

        mat3f makeModelMatrixForTexture( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation );

        mat3f makeClippingMatrixForTexture( const CTexture2D& texture );
        
        void makeBatches();
    };

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_H__