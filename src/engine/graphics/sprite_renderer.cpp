#include "sprite_renderer.hpp"

#include "engine/libs.hpp"
#include "engine/debug/debug.hpp"

namespace chestnut
{   
    CSpriteRenderer::CSpriteRenderer( const CShaderProgram& spriteShader ) 
    : m_shader( spriteShader )
    {
        if( m_shader.isValid() )
        {
            setShaderVariableNames( "aPos", "aTexCoord", "uModel", "uView", "uProjection", "uTexClip" );
            initBuffers();
        }
    }

    CSpriteRenderer::~CSpriteRenderer() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    void CSpriteRenderer::initBuffers() 
    {
        float vertices[] =
        {
             // pos                // uv      
             0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // bottom left
             0.0f,  0.0f,  0.0f,   0.0f, 0.0f, // top left
             1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top right
             1.0f,  1.0f,  0.0f,   1.0f, 1.0f  // bottom right
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        m_shader.bind();

        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );
            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );  

            glEnableVertexAttribArray( m_attrPosLoc );
            glVertexAttribPointer( m_attrPosLoc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void *)0 );

            glEnableVertexAttribArray( m_attrTexCoordLoc );
            glVertexAttribPointer( m_attrTexCoordLoc, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void *)( 3 * sizeof( float ) ) );
        glBindVertexArray(0);

        m_shader.unbind();

        unsigned int err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while initializing buffers: " << gluErrorString( err ) );
        }
    }

    bool CSpriteRenderer::setShaderVariableNames( const std::string& attrPos, 
                                                  const std::string& attrTexCoord, 
                                                  const std::string& unifModel,
                                                  const std::string& unifView,
                                                  const std::string& unifProjection,
                                                  const std::string& unifTexClip )
    {
        bool success = true;

        m_shader.bind();

        m_attrPosLoc = m_shader.getAttributeLocation( attrPos );
        if( m_attrPosLoc == -1 ) success = false;

        m_attrTexCoordLoc = m_shader.getAttributeLocation( attrTexCoord );
        if( m_attrTexCoordLoc == -1 ) success = false;

        m_unifModelLoc = m_shader.getUniformLocation( unifModel );
        if( m_unifModelLoc == -1 ) success = false;

        m_unifViewLoc = m_shader.getUniformLocation( unifView );
        if( m_unifViewLoc == -1 ) success = false;

        m_unifProjectionLoc = m_shader.getUniformLocation( unifProjection );
        if( m_unifProjectionLoc == -1 ) success = false;

        m_unifTexClipLoc = m_shader.getUniformLocation( unifTexClip );
        if( m_unifTexClipLoc == -1 ) success = false;

        m_shader.unbind();

        return success;
    }

    void CSpriteRenderer::setProjectionMatrix( const mat4f& mat ) 
    {
        m_shader.bind();
        m_shader.setMatrix4f( m_unifProjectionLoc, mat );
        m_shader.unbind();
    }

    void CSpriteRenderer::setViewMatrix( const mat4f& mat ) 
    {
        m_shader.bind();
        m_shader.setMatrix4f( m_unifViewLoc, mat );
        m_shader.unbind();
    }

    mat4f CSpriteRenderer::makeModelMatrixForTexture( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation ) 
    {
        SRectangle clip = texture.getClippingRect();

        mat4f model;
        // apply pixel size
        model = matMakeScale<float>( clip.w, clip.h, 1.f ) * model; 
        // scale further
        model = matMakeScale<float>( scale.x, scale.y, 1.f ) * model;
        // rotate from upper left corner
        model = matMakeRotationZ<float>( rotation ) * model;
        // move to position
        model = matMakeTranslation<float>( position.x, position.y, 0.f ) * model;

        return model;
    }

    mat3f CSpriteRenderer::makeClippingMatrixForTexture( const CTexture2D& texture ) 
    {
        SRectangle rect;
        float w, h;
        mat3f clip;

        rect = texture.getClippingRect();
        w = (float)texture.getWidth();
        h = (float)texture.getHeight();

        clip = matMakeScale<float>( rect.w / w, rect.h / h ) * clip;
        clip = matMakeTranslation<float>( rect.x / w, rect.y / h ) * clip;

        return clip;
    }

    void CSpriteRenderer::renderSprite( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation ) 
    {
        mat4f model = makeModelMatrixForTexture( texture, position, scale, rotation );
        mat3f clip = makeClippingMatrixForTexture( texture );

        m_shader.bind();
        texture.bind();
        
        m_shader.setMatrix4f( m_unifModelLoc, model );
        m_shader.setMatrix3f( m_unifTexClipLoc, clip );

        glBindVertexArray( m_vao );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray(0);

        texture.unbind();
        m_shader.unbind();

        unsigned int err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while rednering a sprite: " << gluErrorString( err ) );
        }
    }

} // namespace chestnut
