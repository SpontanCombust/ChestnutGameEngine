#include "chestnut/engine/graphics/renderers/text_renderer.hpp"

#include "chestnut/engine/maths/vector_cast.hpp"
#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource_manager.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"
#include "chestnut/engine/graphics/opengl/vertex_attribute_array.hpp"

#include <unordered_map>

namespace chestnut::engine
{
    bool CTextRenderer::setShaderProgram()
    {
        auto shader = CResourceManager::getOrLoadResource<CShaderProgramResource>(
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.vert", 
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/text.frag"
        );

        if(shader) {
            m_shader = CShaderProgram(shader.value());
        } else {
            LOG_ERROR(shader.error());
            return false;
        }
        
        return true;
    }

    bool CTextRenderer::initBuffers() 
    {
        try
        {
            m_vbo = std::make_shared<CBuffer>(
                CBuffer::EType::VERTEX,
                CBuffer::EUsage::DYNAMIC_DRAW,
                CBuffer::ELayout::ARRAY_OF_STRUCTS
            );

            m_vao.addBuffer(m_vbo, {
                m_shader.getAttribute<vec3f>( "avColor" ).value(),
                m_shader.getAttribute<vec2f>( "avPos" ).value(),
                m_shader.getAttribute<vec2f>( "avUV" ).value(),
                m_shader.getAttribute<vec2f>( "avTranslation" ).value(),
                m_shader.getAttribute<vec2f>( "avScale" ).value()
            });


            m_ibo = std::make_shared<CBuffer>(
                CBuffer::EType::INDEX,
                CBuffer::EUsage::DYNAMIC_DRAW,
                CBuffer::ELayout::SINGLE_ARRAY
            );
            
            m_vao.addBuffer(m_ibo);


            m_vao.compose();
        }
        catch(const tl::bad_optional_access& e)
        {
            return false;
        }

        return true;
    }

    void CTextRenderer::onInit() 
    {
        m_glyphCapacity = 0;
        reserveBufferSpace( CHESTNUT_TEXT_RENDERER_INIT_GLYPH_CAPACITY );
    }

    void CTextRenderer::reserveBufferSpace( GLsizei targetGlyphCapacity ) 
    {
        m_shader.bind();

        if( targetGlyphCapacity > m_glyphCapacity )
        {
            m_vbo->reserve(
                targetGlyphCapacity * sizeof( STextRender_Vertex ) * 4
            );

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
            
            m_ibo->update(
                vecElements.data(),
                targetGlyphCapacity * sizeof( GLuint ) * 6
            );
            
            m_glyphCapacity = targetGlyphCapacity;
        }
    }

    void CTextRenderer::clear() 
    {
        m_vecVertexGroups.clear();
        m_vecBatches.clear();
    }

    void CTextRenderer::submitText( const CText& text, vec2f translation, vec2f scale ) 
    {
        const auto& vecTextLines = text.getData();

        if( vecTextLines.empty() )
        {
            LOG_INFO( "Received text with no data to it. Try using generateData() on the CText." );
            return;
        }


        std::unordered_map< GLuint, STextRender_VertexGroup > mapTexIDToVertexGroup;

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

        for( const auto& vertexGroup : m_vecVertexGroups )
        {
            vertexCount = vertexGroup.vecVertices.size();
            vertexSizeBytes = sizeof( STextRender_Vertex ) * vertexCount;
            elementCount = vertexCount / 4 * 6;

            m_vbo->update(
                vertexGroup.vecVertices.data(),
                vertexSizeBytes,
                vertexOffsetBytes
            );

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
        m_shader.bind();

        prepareBuffers();

        GLuint previousTexID = 0;

        m_vao.bind();
        for( const STextRender_Batch& batch : m_vecBatches )
        {
            if( batch.texID != previousTexID )
            {
                glBindTexture( GL_TEXTURE_2D, batch.texID );
            }

            glDrawElements( GL_TRIANGLES, batch.elementCount, GL_UNSIGNED_INT, (void *)( sizeof( GLuint ) * batch.elementOffset ) );
            
            previousTexID = batch.texID;
        }
        m_vao.unbind();
    }

    void CTextRenderer::render( const CFramebuffer& targetFramebuffer ) 
    {
        m_shader.bind();

        prepareBuffers();

        GLuint previousTexID = 0;

        targetFramebuffer.bind();

        m_vao.bind();
        for( const STextRender_Batch& batch : m_vecBatches )
        {
            if( batch.texID != previousTexID )
            {
                glBindTexture( GL_TEXTURE_2D, batch.texID );
            }

            glDrawElements( GL_TRIANGLES, batch.elementCount, GL_UNSIGNED_INT, (void *)( sizeof( GLuint ) * batch.elementOffset ) );
            
            previousTexID = batch.texID;
        }
        m_vao.unbind();

        targetFramebuffer.unbind();
    }

} // namespace chestnut::engine
