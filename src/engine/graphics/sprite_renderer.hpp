#ifndef __CHESTNUT_SPRITE_RENDERER_H__
#define __CHESTNUT_SPRITE_RENDERER_H__

#include "shader_program.hpp"
#include "texture2d.hpp"
#include "engine/maths/matrix4.hpp"
#include "engine/maths/vector2.hpp"

namespace chestnut
{
    class CSpriteRenderer
    {
    private:
        unsigned int m_vbo;
        unsigned int m_ebo;
        unsigned int m_vao;

        CShaderProgram m_shader;

        int m_attrPosLoc;
        int m_attrTexCoordLoc;

        int m_unifModelLoc;
        int m_unifViewLoc;
        int m_unifProjectionLoc;
        int m_unifTexClipLoc;

    public:
        CSpriteRenderer( const CShaderProgram& spriteShader );
        ~CSpriteRenderer();

        bool setShaderVariableNames( const std::string& attrPos, 
                                     const std::string& attrTexCoord, 
                                     const std::string& unifModel,
                                     const std::string& unifView,
                                     const std::string& unifProjection,
                                     const std::string& unifTexClip );

        void setProjectionMatrix( const mat4f& mat );

        void setViewMatrix( const mat4f& mat );

        void renderSprite( const CTexture2D& texture, const vec2f& position, const vec2f& scale = { 1.f, 1.f }, double rotation = 0.0 );

    private:
        void initBuffers();

        mat4f makeModelMatrixForTexture( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation );

        mat3f makeClippingMatrixForTexture( const CTexture2D& texture );
    };

} // namespace chestnut

#endif // __CHESTNUT_SPRITE_RENDERER_H__