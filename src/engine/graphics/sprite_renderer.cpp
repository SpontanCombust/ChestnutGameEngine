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
        assert( setShaderVariableNames( "aPos", "aUV", "uView", "uProjection" ) );
        
        m_shader.bind();

        initBuffers();
        initLookupVertices();
        reserveBufferSpace( INIT_SPRITE_CAPACITY );

        m_shader.unbind();
    }

    CSpriteRenderer::~CSpriteRenderer() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    void CSpriteRenderer::bindShader() 
    {
        m_shader.bind();
    }

    void CSpriteRenderer::unbindShader() 
    {
        m_shader.unbind();
    }

    bool CSpriteRenderer::setShaderVariableNames( const std::string& attrPos, 
                                                  const std::string& attrUV, 
                                                  const std::string& unifView,
                                                  const std::string& unifProjection )
    {
        bool success = true;

        m_attrPosLoc = m_shader.getAttributeLocation( attrPos );
        if( m_attrPosLoc == -1 ) success = false;

        m_attrUVLoc = m_shader.getAttributeLocation( attrUV );
        if( m_attrUVLoc == -1 ) success = false;

        m_unifViewLoc = m_shader.getUniformLocation( unifView );
        if( m_unifViewLoc == -1 ) success = false;

        m_unifProjectionLoc = m_shader.getUniformLocation( unifProjection );
        if( m_unifProjectionLoc == -1 ) success = false;

        return success;
    }

    void CSpriteRenderer::initBuffers() 
    {
        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );
            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );

            glEnableVertexAttribArray( m_attrPosLoc );
            glVertexAttribPointer( m_attrPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STexturedVertex ), (void *)0 );

            glEnableVertexAttribArray( m_attrUVLoc );
            glVertexAttribPointer( m_attrUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STexturedVertex ), (void *)sizeof( vec2f ) );
        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while initializing buffers: " << gluErrorString( err ) );
        }
    }

    void CSpriteRenderer::initLookupVertices() 
    {
        // upper left
        m_lookupBaseVertices[0].pos = m_lookupBaseVertices[0].uv = { 0.f, 0.f };
        // upper right
        m_lookupBaseVertices[1].pos = m_lookupBaseVertices[1].uv = { 1.f, 0.f };
        // lower right
        m_lookupBaseVertices[2].pos = m_lookupBaseVertices[2].uv = { 1.f, 1.f };
        // lower left
        m_lookupBaseVertices[3].pos = m_lookupBaseVertices[3].uv = { 0.f, 1.f };
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
        // contents of VBO will be changed every tick with glBufferSubData, so dynamic draw and null a data pointer
        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferData( GL_ARRAY_BUFFER, 4 * sizeof( STexturedVertex ) * targetSpriteCapacity, nullptr, GL_DYNAMIC_DRAW ); // 4 vertices per sprite


        GLuint index = 0;
        std::vector< GLuint > indices;
        for (int i = 0; i < targetSpriteCapacity; i++)
        {
            indices.push_back( index + 0 );
            indices.push_back( index + 1 );
            indices.push_back( index + 2 );
            indices.push_back( index + 2 );
            indices.push_back( index + 3 );
            indices.push_back( index + 0 );
            index += 4;
        }

        // we can set indices already at the step of allocating EBO
        // EBO operates on continuous VBO, which is always drawn in the same order, only maybe with different amounts of selected textures
        // indices here are only dictated by the size of buffer
        // so even if there will be less vertices than there are indices for them it doesn't matter,
        // because we can still control the amount of indices being computed by GPU
        // static draw, because we won't have to change it once it's allocated
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof( GLuint ) * targetSpriteCapacity, indices.data(), GL_STATIC_DRAW ); // 6 indices per sprite

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while reserving buffer space: " << gluErrorString( err ) );
        }

        m_spriteCapacity = targetSpriteCapacity;
    }

    mat3f CSpriteRenderer::makeModelMatrixForTexture( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation ) 
    {
        SRectangle clip = texture.getClippingRect();

        mat3f model;
        // apply pixel size
        model = matMakeScale<float>( clip.w, clip.h ) * model; 
        // scale further
        model = matMakeScale<float>( scale.x(), scale.y() ) * model;
        // rotate from upper left corner
        model = matMakeRotation<float>( rotation ) * model;
        // move to position
        model = matMakeTranslation<float>( position.x(), position.y() ) * model;

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

    void CSpriteRenderer::clear() 
    {
        for( auto& [ id, vec ] : m_mapTexIDToVecVertices )
        {
            vec.clear();
        }

        m_vecBatches.clear();
    }

    void CSpriteRenderer::submitSprite( const CTexture2D& texture, const vec2f& position, const vec2f& scale, double rotation ) 
    {
        STexturedVertex vertices[4];

        mat3f model = makeModelMatrixForTexture( texture, position, scale, rotation );
        mat3f clip = makeClippingMatrixForTexture( texture );

        // transforming normalized base vertices into target vertices for sprite
        for (int i = 0; i < 4; i++)
        {
            vertices[i].pos = model * m_lookupBaseVertices[i].pos;
            vertices[i].uv = clip * m_lookupBaseVertices[i].uv;
        }

        auto& vec = m_mapTexIDToVecVertices[ texture.getID() ];
        vec.push_back( vertices[0] );
        vec.push_back( vertices[1] );
        vec.push_back( vertices[2] );
        vec.push_back( vertices[3] );
    }

    void CSpriteRenderer::makeBatches() 
    {
        GLsizei spriteCount = 0;
        for( const auto& [ id, vec ] : m_mapTexIDToVecVertices )
        {
            spriteCount += vec.size() / 4;
        }

        if( spriteCount > m_spriteCapacity )
        {
            reserveBufferSpace( spriteCount );
        }

        SSpriteBatch batch;
        size_t vertexSize;
        size_t vertexOffset;
        int elementAmount;
        size_t elementSize;
        size_t elementOffset;

        vertexOffset = 0;
        elementOffset = 0;
        for( const auto& [ id, vec ] : m_mapTexIDToVecVertices )
        {
            vertexSize = vec.size() * sizeof( STexturedVertex );
            elementAmount = vec.size() / 4 * 6; // 6 indices per 4 vertices
            elementSize = elementAmount * sizeof( GLuint );

            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferSubData( GL_ARRAY_BUFFER, (GLintptr)vertexOffset, (GLsizeiptr)vertexSize, (void *)vec.data() );

            batch.texID = id;
            batch.elementOffset = elementOffset;
            batch.elementAmount = elementAmount;
            m_vecBatches.push_back( batch );

            vertexOffset += vertexSize;
            elementOffset += elementSize;
        }
    }

    void CSpriteRenderer::render() 
    {
        makeBatches();

        glBindVertexArray( m_vao );
        for( const SSpriteBatch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            glDrawElements( GL_TRIANGLES, (GLsizei)batch.elementAmount, GL_UNSIGNED_INT, (void *)batch.elementOffset );
        }
        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_CHANNEL( "SPRITE_RENDERER", "Error occured while rendering: " << gluErrorString( err ) );
        }
    }

} // namespace chestnut
