#include "sprite_renderer.hpp"

#include "engine/globals.hpp"
#include "engine/debug/debug.hpp"
#include "engine/maths/vector_transform.hpp"
#include "engine/maths/vector_cast.hpp"

#include <cassert>
#include <numeric>

#define INIT_SPRITE_CAPACITY 100

namespace chestnut
{   
    CSpriteRenderer::CSpriteRenderer( const CShaderProgram& shader ) 
    {
        m_shader = shader;
        assert( m_shader.isValid() );
        assert( setShaderVariableNames( "avPos", "avUVPos", "aiTransl", "aiScale", "aiRot", "aiClipRect", "uTexSize", "uView", "uProjection" ) );
        
        m_shader.bind();

        initBuffers();
        reserveBufferSpace( INIT_SPRITE_CAPACITY );

        m_shader.unbind();
    }

    CSpriteRenderer::~CSpriteRenderer() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vboInst );
    }

    void CSpriteRenderer::bindShader() 
    {
        m_shader.bind();
    }

    void CSpriteRenderer::unbindShader() 
    {
        m_shader.unbind();
    }

    bool CSpriteRenderer::setShaderVariableNames( const std::string& attrVertPos,
                                                  const std::string& attrVertUVPos, 
                                                  const std::string& attrInstTransl,
                                                  const std::string& attrInstScale,
                                                  const std::string& attrInstRot,
                                                  const std::string& attrInstClipRect,
                                                  const std::string& unifTexSize,
                                                  const std::string& unifView,
                                                  const std::string& unifProjection )
    {
        bool success = true;

        m_attrVertPosLoc = m_shader.getAttributeLocation( attrVertPos );
        if( m_attrVertPosLoc == -1 ) success = false;

        m_attrVertUVPosLoc = m_shader.getAttributeLocation( attrVertUVPos );
        if( m_attrVertUVPosLoc == -1 ) success = false;


        m_attrInstTranslLoc = m_shader.getAttributeLocation( attrInstTransl );
        if( m_attrInstTranslLoc == -1 ) success = false;

        m_attrInstScaleLoc = m_shader.getAttributeLocation( attrInstScale );
        if( m_attrInstScaleLoc == -1 ) success = false;

        m_attrInstRotLoc = m_shader.getAttributeLocation( attrInstRot );
        if( m_attrInstRotLoc == -1 ) success = false;

        m_attrInstClipRectLoc = m_shader.getAttributeLocation( attrInstClipRect );
        if( m_attrInstClipRectLoc == -1 ) success = false;


        m_unifTexSizeLoc = m_shader.getUniformLocation( unifTexSize );
        if( m_unifTexSizeLoc == -1 ) success = false;

        m_unifViewLoc = m_shader.getUniformLocation( unifView );
        if( m_unifViewLoc == -1 ) success = false;

        m_unifProjectionLoc = m_shader.getUniformLocation( unifProjection );
        if( m_unifProjectionLoc == -1 ) success = false;

        return success;
    }

    void CSpriteRenderer::initBuffers() 
    {
        GLfloat vertices[] = {
            // pos      // uv
            0.0, 0.0,   0.0, 0.0,   // upper left
            1.0, 0.0,   1.0, 0.0,   // upper right
            1.0, 1.0,   1.0, 1.0,   // lower right
            0.0, 1.0,   0.0, 1.0    // lower left
        };

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glGenBuffers( 1, &m_vboVert );
        glGenBuffers( 1, &m_vboInst );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

            glBindBuffer( GL_ARRAY_BUFFER, m_vboVert );
            glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

            glEnableVertexAttribArray( m_attrVertPosLoc );
            glVertexAttribPointer( m_attrVertPosLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void *)0 );

            glEnableVertexAttribArray( m_attrVertUVPosLoc );
            glVertexAttribPointer( m_attrVertUVPosLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof( float ), (void *)( 2 * sizeof( float ) ) );


            glBindBuffer( GL_ARRAY_BUFFER, m_vboInst );

            glEnableVertexAttribArray( m_attrInstTranslLoc );
            glVertexAttribPointer( m_attrInstTranslLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SSpriteInstance ), (void *)offsetof( SSpriteInstance, transl ) );
            glVertexAttribDivisor( m_attrInstTranslLoc, 1 );

            glEnableVertexAttribArray( m_attrInstScaleLoc );
            glVertexAttribPointer( m_attrInstScaleLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SSpriteInstance ), (void *)offsetof( SSpriteInstance, scale ) );
            glVertexAttribDivisor( m_attrInstScaleLoc, 1 );

            glEnableVertexAttribArray( m_attrInstRotLoc );
            glVertexAttribPointer( m_attrInstRotLoc, 1, GL_FLOAT, GL_FALSE, sizeof( SSpriteInstance ), (void *)offsetof( SSpriteInstance, rot ) );
            glVertexAttribDivisor( m_attrInstRotLoc, 1 );

            glEnableVertexAttribArray( m_attrInstClipRectLoc );
            glVertexAttribPointer( m_attrInstClipRectLoc, 4, GL_FLOAT, GL_FALSE, sizeof( SSpriteInstance ), (void *)offsetof( SSpriteInstance, clipRect ) );
            glVertexAttribDivisor( m_attrInstClipRectLoc, 1 );

        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while initializing buffers: " << gluErrorString( err ) );
        }
    }

    void CSpriteRenderer::setProjectionMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifProjectionLoc, mat );
    }

    void CSpriteRenderer::setViewMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifViewLoc, mat );
    }

    void CSpriteRenderer::reserveBufferSpace( GLsizei targetSpriteCapacity ) 
    {
        // contents of instance VBO will be changed every tick with glBufferSubData, so dynamic draw and null a data pointer
        glBindBuffer( GL_ARRAY_BUFFER, m_vboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( SSpriteInstance ) * targetSpriteCapacity, nullptr, GL_DYNAMIC_DRAW ); // 4 vertices per sprite

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while reserving buffer space: " << gluErrorString( err ) );
        }

        m_spriteCapacity = targetSpriteCapacity;
    }

    void CSpriteRenderer::clear() 
    {
        for( auto& [ id, vec ] : m_mapTexIDToVecInstances )
        {
            vec.clear();
        }

        m_vecBatches.clear();
    }

    void CSpriteRenderer::submitSprite( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation ) 
    {
        GLuint id;
        int w, h;
        SRectangle rect;

        id = texture.getID();
        w = texture.getWidth();
        h = texture.getHeight();
        rect = texture.getClippingRect();

        SSpriteInstance instance;
        instance.transl = position;
        instance.scale = scale;
        instance.rot = (float)rotation;
        instance.clipRect = vec4f( rect.x, rect.y, rect.w, rect.h );      

        auto& vec = m_mapTexIDToVecInstances[id];
        vec.push_back( instance );

        m_mapTexIDToSize[id] = vec2f( (float)w, (float)h );
    }

    void CSpriteRenderer::makeBatches() 
    {
        GLsizei spriteCount = 0;
        for( const auto& [ id, vec ] : m_mapTexIDToVecInstances )
        {
            spriteCount += vec.size();
        }

        if( spriteCount > m_spriteCapacity )
        {
            reserveBufferSpace( spriteCount );
        }

        SSpriteBatch batch;
        size_t instanceSizeBytes;
        GLsizei instanceAmount;
        GLuint instanceOffset;
        size_t instanceOffsetBytes;

        instanceOffset = 0;
        instanceOffsetBytes = 0;
        for( const auto& [ id, vec ] : m_mapTexIDToVecInstances )
        {
            instanceAmount = vec.size(); // 6 indices per 4 vertices
            instanceSizeBytes = instanceAmount * sizeof( SSpriteInstance );

            glBindBuffer( GL_ARRAY_BUFFER, m_vboInst );
            glBufferSubData( GL_ARRAY_BUFFER, (GLintptr)instanceOffsetBytes, (GLsizeiptr)instanceSizeBytes, (void *)vec.data() );

            batch.texID = id;
            batch.instanceOffset = instanceOffset;
            batch.instanceAmount = instanceAmount;
            m_vecBatches.push_back( batch );

            instanceOffset += instanceAmount;
            instanceOffsetBytes += instanceSizeBytes;
        }
    }

    void CSpriteRenderer::render() 
    {
        makeBatches();

        glBindVertexArray( m_vao );
        for( const SSpriteBatch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            m_shader.setVector2f( m_unifTexSizeLoc, m_mapTexIDToSize[ batch.texID ] );
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, batch.instanceAmount, batch.instanceOffset );
        }
        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while rendering: " << gluErrorString( err ) );
        }
    }

} // namespace chestnut
