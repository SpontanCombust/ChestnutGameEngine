#include "text_renderer.hpp"

#include "../debug/log.hpp"
#include "../maths/vector_cast.hpp"

#include <unordered_map>

#define INIT_GLYPH_CAPACITY 128

namespace chestnut::engine
{
    void CTextRenderer::onInit() 
    {
        m_glyphCapacity = 0;
        reserveBufferSpace( INIT_GLYPH_CAPACITY );
    }

    void CTextRenderer::deleteBuffers() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    void CTextRenderer::initBuffers() 
    {
        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );

            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );

            glEnableVertexAttribArray( m_attrVertColorLoc );
            glVertexAttribPointer( m_attrVertColorLoc, 3, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, color ) );

            glEnableVertexAttribArray( m_attrVertPosLoc );
            glVertexAttribPointer( m_attrVertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, pos ) );

            glEnableVertexAttribArray( m_attrVertUVLoc );
            glVertexAttribPointer( m_attrVertUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof( STextRender_Vertex ), (void *)offsetof( STextRender_Vertex, uv ) );

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
                LOG_ERROR( "Error occured while initializing buffers: " << gluErrorString( err ) );
            }

            m_glyphCapacity = targetGlyphCapacity;
        }
    }

    bool CTextRenderer::setShaderVariableLocations() 
    {
        m_attrVertPosLoc            = m_shader.getAttributeLocation( "avPos" );
        m_attrVertUVLoc             = m_shader.getAttributeLocation( "avUV" );
        m_attrVertColorLoc          = m_shader.getAttributeLocation( "avColor" );
        m_attrVertTranslationLoc    = m_shader.getAttributeLocation( "avTranslation" );
        m_attrVertScaleLoc          = m_shader.getAttributeLocation( "avScale" );

        if(    m_attrVertPosLoc         == -1 
            || m_attrVertUVLoc          == -1
            || m_attrVertColorLoc       == -1
            || m_attrVertTranslationLoc == -1
            || m_attrVertScaleLoc       == -1 )
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
        if( !text.isEmpty() )
        {
            std::unordered_map< GLuint, STextRender_VertexGroup > mapTexIDToVertexGroup;
            
            const auto& vecTextLines = text.getData();
            for( const internal::STextLine& textLine : vecTextLines )
            {
                for( const internal::STextGlyph& textGlyph : textLine.vecGlyphs )
                {
                    STextRender_Vertex vertex;

                    vertex.color = textGlyph.color;
                    vertex.translation = translation;
                    vertex.scale = scale;

                    // upper left
                    vertex.pos = vecCastType<float>( textLine.offset + textGlyph.lineOffset );
                    vertex.uv = textGlyph.uvOffsetNorm;
                    mapTexIDToVertexGroup[ textGlyph.texID ].vecVertices.push_back( vertex );
                    
                    // upper right
                    vertex.pos = vecCastType<float>( textLine.offset + textGlyph.lineOffset + vec2i( textGlyph.size.x, 0 ) );
                    vertex.uv = textGlyph.uvOffsetNorm + vec2f( textGlyph.uvSizeNorm.x, 0 );
                    mapTexIDToVertexGroup[ textGlyph.texID ].vecVertices.push_back( vertex );

                    // lower right
                    vertex.pos = vecCastType<float>( textLine.offset + textGlyph.lineOffset + textGlyph.size );
                    vertex.uv = textGlyph.uvOffsetNorm + textGlyph.uvSizeNorm;
                    mapTexIDToVertexGroup[ textGlyph.texID ].vecVertices.push_back( vertex );

                    // lower left
                    vertex.pos = vecCastType<float>( textLine.offset + textGlyph.lineOffset + vec2i( 0, textGlyph.size.y ) );
                    vertex.uv = textGlyph.uvOffsetNorm + vec2f( 0, textGlyph.uvSizeNorm.y );
                    mapTexIDToVertexGroup[ textGlyph.texID ].vecVertices.push_back( vertex );
                }
            }

            for( auto& [ texID , vertexGroup ] : mapTexIDToVertexGroup )
            {
                // IDs weren't set before for actual vertex groups, so we're doing it now
                vertexGroup.texID = texID;
                m_vecVertexGroups.push_back( vertexGroup );
            }
        }       
    }

    void CTextRenderer::prepareBuffers() 
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
        prepareBuffers();

        GLuint previousTexID = 0;

        glBindVertexArray( m_vao );
        for( const STextRender_Batch& batch : m_vecBatches )
        {
            if( batch.texID != previousTexID )
            {
                glBindTexture( GL_TEXTURE_2D, batch.texID );
            }

            glDrawElements( GL_TRIANGLES, batch.elementCount, GL_UNSIGNED_INT, (void *)( sizeof( GLuint ) * batch.elementOffset ) );
            
            previousTexID = batch.texID;
        }
        glBindVertexArray(0);
    }

} // namespace chestnut::engine
