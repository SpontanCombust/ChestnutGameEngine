#include "sprite_renderer.hpp"

#include "../debug/log.hpp"
#include "../macros.hpp"

namespace chestnut::engine
{   
    static const uint8_t missingTextureBytes[] = 
    {
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,
        0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,
        0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff,   0x00, 0x00, 0x00,   0xff, 0x00, 0xff
    };

    void CSpriteRenderer::onInit() 
    {
        m_spriteCapacity = 0;
        reserveBufferSpace( CHESTNUT_SPRITE_RENDERER_INIT_SPRITE_CAPACITY );

        m_missingTexturePlaceholder = CTexture2D( CTexture2DResource::loadFromPixels( (void *)missingTextureBytes, 8, 8, GL_RGB, true ) );
        m_missingTexturePlaceholder.setFiltering( GL_NEAREST, GL_NEAREST );
    }

    void CSpriteRenderer::deleteBuffers() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vboVert );
        glDeleteBuffers( 1, &m_vboInst );
    }

    bool CSpriteRenderer::setShaderVariableLocations()
    {
        m_attrVertPosLoc        = m_shader.getAttributeLocation( "avPos" );
        m_attrVertUVPosLoc      = m_shader.getAttributeLocation( "avUVPos" );

        m_attrInstOriginLoc     = m_shader.getAttributeLocation( "aiOrigin" );
        m_attrInstTranslLoc     = m_shader.getAttributeLocation( "aiTransl" );
        m_attrInstScaleLoc      = m_shader.getAttributeLocation( "aiScale" );
        m_attrInstRotLoc        = m_shader.getAttributeLocation( "aiRot" );
        m_attrInstClipRectLoc   = m_shader.getAttributeLocation( "aiClipRect" );
        m_attrInstTint          = m_shader.getAttributeLocation( "aiTint" );
        m_attrInstTintFactor    = m_shader.getAttributeLocation( "aiTintFactor" );

        m_unifTexSizeLoc        = m_shader.getUniformLocation( "uTexSize" );

        if(    m_attrVertPosLoc         == -1 
            || m_attrVertUVPosLoc       == -1
            || m_attrInstOriginLoc      == -1
            || m_attrInstTranslLoc      == -1
            || m_attrInstScaleLoc       == -1 
            || m_attrInstRotLoc         == -1
            || m_attrInstClipRectLoc    == -1
            || m_attrInstTint           == -1
            || m_attrInstTintFactor     == -1
            || m_unifTexSizeLoc         == -1 )
        {
            return false;
        }

        return true;
    }

    void CSpriteRenderer::initBuffers() 
    {
        GLfloat vertices[] = {
            // pos      // uv
            0.0, 0.0,   0.0, 1.0,   // upper left
            1.0, 0.0,   1.0, 1.0,   // upper right
            1.0, 1.0,   1.0, 0.0,   // lower right
            0.0, 1.0,   0.0, 0.0    // lower left
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

            glEnableVertexAttribArray( m_attrInstOriginLoc );
            glVertexAttribPointer( m_attrInstOriginLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, origin ) );
            glVertexAttribDivisor( m_attrInstOriginLoc, 1 );

            glEnableVertexAttribArray( m_attrInstTranslLoc );
            glVertexAttribPointer( m_attrInstTranslLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, transl ) );
            glVertexAttribDivisor( m_attrInstTranslLoc, 1 );

            glEnableVertexAttribArray( m_attrInstScaleLoc );
            glVertexAttribPointer( m_attrInstScaleLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, scale ) );
            glVertexAttribDivisor( m_attrInstScaleLoc, 1 );

            glEnableVertexAttribArray( m_attrInstRotLoc );
            glVertexAttribPointer( m_attrInstRotLoc, 1, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, rot ) );
            glVertexAttribDivisor( m_attrInstRotLoc, 1 );

            glEnableVertexAttribArray( m_attrInstClipRectLoc );
            glVertexAttribPointer( m_attrInstClipRectLoc, 4, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, clipRect ) );
            glVertexAttribDivisor( m_attrInstClipRectLoc, 1 );

            glEnableVertexAttribArray( m_attrInstTint );
            glVertexAttribPointer( m_attrInstTint, 3, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, tint ) );
            glVertexAttribDivisor( m_attrInstTint, 1 );

            glEnableVertexAttribArray( m_attrInstTintFactor );
            glVertexAttribPointer( m_attrInstTintFactor, 1, GL_FLOAT, GL_FALSE, sizeof( SSpriteRender_Instance ), (void *)offsetof( SSpriteRender_Instance, tintFactor ) );
            glVertexAttribDivisor( m_attrInstTintFactor, 1 );

        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while initializing buffers: " << gluErrorString( err ) );
        }
    }

    void CSpriteRenderer::reserveBufferSpace( GLsizei targetSpriteCapacity ) 
    {
        if( targetSpriteCapacity <= m_spriteCapacity )
        {
            return;
        }
        
        // contents of instance VBO will be changed every tick with glBufferSubData, so dynamic draw and null a data pointer
        glBindBuffer( GL_ARRAY_BUFFER, m_vboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( SSpriteRender_Instance ) * targetSpriteCapacity, nullptr, GL_DYNAMIC_DRAW ); // 4 vertices per sprite

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while reserving buffer space: " << gluErrorString( err ) );
        }

        m_spriteCapacity = targetSpriteCapacity;
    }

    void CSpriteRenderer::clear() 
    {
        m_mapTexIDToInstanceGroup.clear();
        m_vecBatches.clear();
    }

    void CSpriteRenderer::submitSprite( const CTexture2D& texture, const vec2f& translation, const vec2f& origin, const vec2f& scale, double rotation ) 
    {
        GLuint id;
        int w, h;
        SRectangle rect;

        if( texture.isValid() )
        {
            id = texture.getID();
            w = texture.getWidth();
            h = texture.getHeight();
            rect = texture.getClippingRect();
        }
        else
        {
            id = m_missingTexturePlaceholder.getID();
            w = m_missingTexturePlaceholder.getWidth();
            h = m_missingTexturePlaceholder.getHeight();
            rect = m_missingTexturePlaceholder.getClippingRect();
        }
        

        SSpriteRender_Instance instance;
        instance.origin = origin;
        instance.transl = translation;
        instance.scale = scale;
        instance.rot = (float)rotation;
        instance.clipRect = vec4f( rect.x, 1.f - rect.y - rect.h, rect.w, rect.h ); // we have to shift Y around to adapt it to OpenGL's way of handling texture coords
        instance.tint = texture.getTint();
        instance.tintFactor = texture.getTintFactor();  

        auto& group = m_mapTexIDToInstanceGroup[id];
        group.texID = id;
        group.texSize = { (float)w, (float)h };
        group.vecInstances.push_back( instance );
    }

    void CSpriteRenderer::prepareBuffers() 
    {
        GLsizei spriteCount = 0;
        for( const auto& [ id, group ] : m_mapTexIDToInstanceGroup )
        {
            spriteCount += group.vecInstances.size();
        }

        if( spriteCount > m_spriteCapacity )
        {
            reserveBufferSpace( spriteCount );
        }

        GLsizei instanceAmount;
        size_t instanceSizeBytes;
        GLuint instanceOffset;
        size_t instanceOffsetBytes;
        SSpriteRender_Batch batch;

        instanceOffset = 0;
        instanceOffsetBytes = 0;
        glBindBuffer( GL_ARRAY_BUFFER, m_vboInst );
        for( const auto& [ id, group ] : m_mapTexIDToInstanceGroup )
        {
            instanceAmount = group.vecInstances.size();
            instanceSizeBytes = instanceAmount * sizeof( SSpriteRender_Instance );

            glBufferSubData( GL_ARRAY_BUFFER, (GLintptr)instanceOffsetBytes, (GLsizeiptr)instanceSizeBytes, (void *)group.vecInstances.data() );

            batch.texID = group.texID;
            batch.texSize = group.texSize;
            batch.instanceOffset = instanceOffset;
            batch.instanceAmount = instanceAmount;
            m_vecBatches.push_back( batch );

            instanceOffset += instanceAmount;
            instanceOffsetBytes += instanceSizeBytes;
        }
    }

    void CSpriteRenderer::render() 
    {
        prepareBuffers();

        glBindVertexArray( m_vao );
        for( const SSpriteRender_Batch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            m_shader.setVector2f( m_unifTexSizeLoc, batch.texSize );
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, batch.instanceAmount, batch.instanceOffset );
        }
        glBindVertexArray(0);

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while rendering: " << gluErrorString( err ) );
        }
    }

    void CSpriteRenderer::render( const CFramebuffer& targetFramebuffer ) 
    {
        prepareBuffers();

        targetFramebuffer.bind();

        glBindVertexArray( m_vao );
        for( const SSpriteRender_Batch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            m_shader.setVector2f( m_unifTexSizeLoc, batch.texSize );
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, batch.instanceAmount, batch.instanceOffset );
        }
        glBindVertexArray(0);

        targetFramebuffer.unbind();

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while rendering: " << gluErrorString( err ) );
        }
    }

} // namespace chestnut::engine
