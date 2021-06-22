#include "text_renderer.hpp"

#include "engine/debug/debug.hpp"

#include <cassert>

#define INIT_GLYPH_CAPACITY 128

namespace chestnut
{
    CTextRenderer::CTextRenderer( const CShaderProgram& shader ) 
    {
        m_shader = shader;
        assert( m_shader.isValid() );

        m_shader.bind();
        assert( setShaderVariableNames( "avPos", "avUV", "avColor", "avTranslation", "avScale", "uProjection", "uView" ) );

        initBuffers();
        m_glyphCapacity = 0;
        reserveBufferSpace( INIT_GLYPH_CAPACITY );
    }

    CTextRenderer::~CTextRenderer() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    void CTextRenderer::bindShader() 
    {
        m_shader.bind();
    }

    void CTextRenderer::unbindShader() 
    {
        m_shader.unbind();
    }

    void CTextRenderer::setProjectionMatrix( mat4f projection ) 
    {
        m_shader.setMatrix4f( m_unifProjectionLoc, projection );
    }

    void CTextRenderer::setViewMatrix( mat4f view ) 
    {
        m_shader.setMatrix4f( m_unifViewLoc, view );
    }

    void CTextRenderer::initBuffers() 
    {
        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );

            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );

            glEnableVertexAttribArray( m_attrVertPosLoc );
            glVertexAttribPointer( m_attrVertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, pos ) );

            glEnableVertexAttribArray( m_attrVertUVLoc );
            glVertexAttribPointer( m_attrVertUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, uv ) );

            glEnableVertexAttribArray( m_attrVertColorLoc );
            glVertexAttribPointer( m_attrVertColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, color ) );

            glEnableVertexAttribArray( m_attrVertTranslationLoc );
            glVertexAttribPointer( m_attrVertTranslationLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, translation ) );

            glEnableVertexAttribArray( m_attrVertScaleLoc );
            glVertexAttribPointer( m_attrVertScaleLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, scale ) );

        glBindVertexArray( 0 );
    }

    void CTextRenderer::reserveBufferSpace( GLsizei targetGlyphCapacity ) 
    {
        if( targetGlyphCapacity > m_glyphCapacity )
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferData( GL_ARRAY_BUFFER, targetGlyphCapacity * sizeof( STextRender_Vertex ) * 4, nullptr, GL_DYNAMIC_DRAW );


            std::vector< GLuint > vecElements;
            GLuint elementOffset = 0;
            vecElements.reserve( targetGlyphCapacity * 6 );
            for (GLsizei i = 0; i < targetGlyphCapacity; i++)
            {
                vecElements.push_back( elementOffset + 0 );    
                vecElements.push_back( elementOffset + 1 );    
                vecElements.push_back( elementOffset + 2 );    
                vecElements.push_back( elementOffset + 2 );    
                vecElements.push_back( elementOffset + 3 );    
                vecElements.push_back( elementOffset + 0 );
                elementOffset += 4;
            }
            
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
            glBufferData( GL_ELEMENT_ARRAY_BUFFER, targetGlyphCapacity * sizeof( GLuint ) * 6, vecElements.data(), GL_STATIC_DRAW );


            GLenum err = glGetError();
            if( err != GL_NO_ERROR )
            {
                LOG_CHANNEL( "TEXT_RENDERER", "Error occured while initializing buffers: " << gluErrorString( err ) );
            }

            m_glyphCapacity = targetGlyphCapacity;
        }
    }

    bool CTextRenderer::setShaderVariableNames( const std::string& attrVertPos,
                                                const std::string& attrVertUV,
                                                const std::string& attrVertColor,
                                                const std::string& attrVertTranslation,
                                                const std::string& attrVertScale,
                                                const std::string& unifProjection,
                                                const std::string& unifView ) 
    {
        m_attrVertPosLoc            = m_shader.getAttributeLocation( attrVertPos );
        m_attrVertUVLoc             = m_shader.getAttributeLocation( attrVertUV );
        m_attrVertColorLoc          = m_shader.getAttributeLocation( attrVertColor );
        m_attrVertTranslationLoc    = m_shader.getAttributeLocation( attrVertTranslation );
        m_attrVertScaleLoc          = m_shader.getAttributeLocation( attrVertScale );

        m_unifProjectionLoc     = m_shader.getUniformLocation( unifProjection );
        m_unifViewLoc           = m_shader.getUniformLocation( unifView );

        if(    m_attrVertPosLoc         == -1 
            || m_attrVertUVLoc          == -1
            || m_attrVertColorLoc       == -1
            || m_attrVertTranslationLoc == -1
            || m_attrVertScaleLoc       == -1 
            || m_unifProjectionLoc      == -1
            || m_unifViewLoc            == -1 )
        {
            return false;
        }

        return true;
    }

    void CTextRenderer::clear() 
    {
        m_vecVertexGroups.clear();
        m_vecBatches.clear();
    }

    void CTextRenderer::submitText( const CText& text, vec2f translation, vec2f scale ) 
    {
        if( text.getLength() > 0 )
        {
            const auto& vecTextFragments = text.getFragments();
            
            for( const STextFragment& textFragment : vecTextFragments )
            {
                STextRender_VertexGroup vertexGroup;
   
                vertexGroup.texID = textFragment.texID;

                for( const STextGlyph& textGlyph : textFragment.vecGlyphs )
                {
                    STextRender_Vertex vertex;

                    vertex.color = textFragment.color;
                    vertex.translation = translation;
                    vertex.scale = scale;

                    // upper left
                    vertex.pos = textGlyph.posOffset;
                    vertex.uv = textGlyph.uvOffsetNorm;
                    vertexGroup.vecVertices.push_back( vertex );
                    
                    // upper right
                    vertex.pos = textGlyph.posOffset + vec2f( textGlyph.size.x(), 0 );
                    vertex.uv = textGlyph.uvOffsetNorm + vec2f( textGlyph.uvSizeNorm.x(), 0 );
                    vertexGroup.vecVertices.push_back( vertex );

                    // lower right
                    vertex.pos = textGlyph.posOffset + textGlyph.size;
                    vertex.uv = textGlyph.uvOffsetNorm + textGlyph.uvSizeNorm;
                    vertexGroup.vecVertices.push_back( vertex );

                    // lower left
                    vertex.pos = textGlyph.posOffset + vec2f( 0, textGlyph.size.y() );
                    vertex.uv = textGlyph.uvOffsetNorm + vec2f( 0, textGlyph.uvSizeNorm.y() );
                    vertexGroup.vecVertices.push_back( vertex );
                }

                m_vecVertexGroups.push_back( vertexGroup );
            }
        }       
    }

    void CTextRenderer::makeBatches() 
    {
        int glyphCount = 0;
        for( const auto& vertexGroup : m_vecVertexGroups )
        {
            glyphCount += vertexGroup.vecVertices.size() / 4;
        }
        if( glyphCount > m_glyphCapacity )
        {
            reserveBufferSpace( glyphCount );
        }


        GLsizei vertexCount;
        GLsizeiptr vertexSizeBytes;
        GLintptr vertexOffsetBytes = 0;
        GLsizei elementCount;
        GLint elementOffset = 0;
        STextRender_Batch batch;

        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        for( const auto& vertexGroup : m_vecVertexGroups )
        {
            vertexCount = vertexGroup.vecVertices.size();
            vertexSizeBytes = sizeof( STextRender_Vertex ) * vertexCount;
            elementCount = vertexCount / 4 * 6;

            glBufferSubData( GL_ARRAY_BUFFER, vertexOffsetBytes, vertexSizeBytes, vertexGroup.vecVertices.data() );

            batch.texID = vertexGroup.texID;
            batch.elementCount = elementCount;
            batch.elementOffset = elementOffset;
            
            m_vecBatches.push_back( batch );

            vertexOffsetBytes += vertexSizeBytes;
            elementOffset += elementCount;
        }
    }

    void CTextRenderer::render() 
    {
        makeBatches();

        glBindVertexArray( m_vao );
        for( const STextRender_Batch& batch : m_vecBatches )
        {
            glBindTexture( GL_TEXTURE_2D, batch.texID );
            glDrawElements( GL_TRIANGLES, batch.elementCount, GL_UNSIGNED_INT, (void *)( sizeof( GLuint ) * batch.elementOffset ) );
        }
        glBindVertexArray(0);
    }

} // namespace chestnut
