#include "chestnut/engine/graphics/renderers/colored_polygon2d_renderer.hpp"

#include "chestnut/engine/debug/log.hpp"
#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/resources/resource_manager.hpp"
#include "chestnut/engine/resources/shader_program_resource.hpp"

namespace chestnut::engine
{
    bool CColoredPolygon2DRenderer::setShaderProgram()
    {
        auto shader = CResourceManager::getOrLoadResource<CShaderProgramResource>(
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.vert", 
            CHESTNUT_ENGINE_ASSETS_DIR_PATH"/shaders/coloredPolygon2D.frag"
        );

        if(shader) {
            m_shader = CShaderProgram(shader.value());
        } else {
            LOG_ERROR(shader.error());
            return false;
        }
        
        return true;
    }

    bool CColoredPolygon2DRenderer::initBuffers() 
    {
        try
        {
            m_vbo = std::make_shared<CBuffer>(
                CBuffer::EType::VERTEX,
                CBuffer::EUsage::DYNAMIC_DRAW,
                CBuffer::ELayout::ARRAY_OF_STRUCTS
            );

            m_vao.addBuffer(m_vbo, {
                m_shader.getAttribute<vec2f>( "avPos" ).value(),
                m_shader.getAttribute<vec4f>( "avColor" ).value(),
                m_shader.getAttribute<vec2f>( "avTransl" ).value(),
                m_shader.getAttribute<vec2f>( "avScale" ).value(),
                m_shader.getAttribute<float>( "avRot" ).value()
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

    void CColoredPolygon2DRenderer::onInit() 
    {
        m_polygonVertexCapacity = 0;
        m_vertexIndexCapacity = 0;
        reserveBufferSpace( CHESTNUT_POLYGON_RENDERER_INIT_VERTEX_CAPACITY, CHESTNUT_POLYGON_RENDERER_INIT_INDEX_CAPACITY );
    }

    void CColoredPolygon2DRenderer::reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity ) 
    {
        m_shader.bind();

        if( targetPolygonVertexCapacity > m_polygonVertexCapacity )
        {
            m_vbo->reserve(sizeof( SColoredPolygon2DRender_Vertex ) * targetPolygonVertexCapacity);
            m_polygonVertexCapacity = targetPolygonVertexCapacity;
        }
        if( targetVertexIndexCapacity > m_vertexIndexCapacity )
        {
            m_ibo->reserve(sizeof( GLuint ) * targetVertexIndexCapacity);
            m_vertexIndexCapacity = targetVertexIndexCapacity;
        }
    }

    void CColoredPolygon2DRenderer::clear() 
    {
        for( auto& [ drawMode, vertexGroup ] : m_mapDrawModeToVertexGroup )
        {
            vertexGroup.vecRenderVertices.clear();
            vertexGroup.vecRenderIndices.clear();
        }

        m_vecBatches.clear();
    }

    bool isPolygon2DRenderable( const SColoredPolygon2D& polygon )
    {
        if( polygon.drawMode == GL_TRIANGLES )
        {
            if( polygon.vecIndices.size() % 3 == 0 )
            {
                return true;
            }

            return false;
        }
        else if ( polygon.drawMode == GL_LINES )
        {
            if( polygon.vecIndices.size() % 2 == 0 )
            {
                return true;
            }

            return false;   
        }
        else
        {
            return true;
        }
    }

    bool isPolygon2DRenderable( const SMulticoloredPolygon2D& polygon )
    {
        if( polygon.drawMode == GL_TRIANGLES )
        {
            if( polygon.vecIndices.size() % 3 == 0 )
            {
                return true;
            }

            return false;
        }
        else if ( polygon.drawMode == GL_LINES )
        {
            if( polygon.vecIndices.size() % 2 == 0 )
            {
                return true;
            }

            return false;   
        }
        else
        {
            return true;
        }
    }

    void CColoredPolygon2DRenderer::submitPolygon( const SColoredPolygon2D& polygonModel, const vec2f& translation, const vec2f& scale, float rotation ) 
    {
        if( !isPolygon2DRenderable( polygonModel ) )
        {
            LOG_WARNING( "Polygon with improper indices cannot be used!" );
            return;
        }

        auto& renderVertexGroup = m_mapDrawModeToVertexGroup[ polygonModel.drawMode ];

        GLuint indexOffset = renderVertexGroup.vecRenderVertices.size(); // this offset is a local offset of vertex group, not the entirety of vertices accross all draw modes

        SColoredPolygon2DRender_Vertex renderVertex;
        for( const SVertex2D& vertex : polygonModel.vecVertices )
        {
            renderVertex.position = vertex.pos;
            renderVertex.color = polygonModel.color;

            renderVertex.translation = translation;
            renderVertex.scale = scale;
            renderVertex.rotation = rotation;

            renderVertexGroup.vecRenderVertices.push_back( renderVertex );
        }

        for( GLuint index : polygonModel.vecIndices )
        {
            renderVertexGroup.vecRenderIndices.push_back( index + indexOffset );
        }
    }

    void CColoredPolygon2DRenderer::submitPolygon( const SMulticoloredPolygon2D& polygonModel, const vec2f& translation, const vec2f& scale, float rotation ) 
    {
        if( !isPolygon2DRenderable( polygonModel ) )
        {
            LOG_WARNING( "Polygon with improper indices cannot be used!" );
            return;
        }

        auto& renderVertexGroup = m_mapDrawModeToVertexGroup[ polygonModel.drawMode ];

        GLuint indexOffset = renderVertexGroup.vecRenderVertices.size(); // this offset is a local offset of vertex group, not the entirety of vertices accross all draw modes

        SColoredPolygon2DRender_Vertex renderVertex;
        for( const SColoredVertex2D& vertex : polygonModel.vecVertices )
        {
            renderVertex.position = vertex.pos;
            renderVertex.color = vertex.color;

            renderVertex.translation = translation;
            renderVertex.scale = scale;
            renderVertex.rotation = rotation;

            renderVertexGroup.vecRenderVertices.push_back( renderVertex );
        }

        for( GLuint index : polygonModel.vecIndices )
        {
            renderVertexGroup.vecRenderIndices.push_back( index + indexOffset );
        }
    }

    void CColoredPolygon2DRenderer::prepareBuffers() 
    {
        GLsizei vertexCount = 0, indexCount = 0;

        for( const auto& [ drawMode, vertexGroup ] : m_mapDrawModeToVertexGroup )
        {
            vertexCount += vertexGroup.vecRenderVertices.size();
            indexCount += vertexGroup.vecRenderIndices.size();
        }

        reserveBufferSpace( vertexCount, indexCount );

        GLsizei vertexOffset = 0, indexOffset = 0;
        for( auto& [ drawMode, vertexGroup ] : m_mapDrawModeToVertexGroup )
        {
            vertexCount = vertexGroup.vecRenderVertices.size();
            indexCount = vertexGroup.vecRenderIndices.size();

            // we have to add one more offset to indices of a vertex group
            // the way it is done now with single buffer with contiguous sections for specific drawing modes
            // and a map to store the data for these modes, there's no easy way of storing valid indices
            // if we can submit polygons with different drawing modes in random order
            // that's why here when we're going over every draw mode in the map we keep track of previously
            // checked vertex group index count and apply an offset to the next one to make these groups be contiguous in the IBO
            // and to not overwrite each other
            for( GLuint& index : vertexGroup.vecRenderIndices )
            {
                index += vertexOffset;
            }

            m_vbo->update(
                vertexGroup.vecRenderVertices.data(),
                sizeof( SColoredPolygon2DRender_Vertex ) * vertexCount,
                sizeof( SColoredPolygon2DRender_Vertex ) * vertexOffset
            );

            m_ibo->update(
                vertexGroup.vecRenderIndices.data(),
                sizeof( GLuint ) * indexCount,
                sizeof( GLuint ) * indexOffset
            );

            SColoredPolygon2DRender_Batch batch;
            batch.drawMode = drawMode;
            batch.indexCount = indexCount;
            batch.indexOffset = indexOffset;
            m_vecBatches.push_back( batch );

            vertexOffset += vertexCount;
            indexOffset += indexCount;
        }

    }

    void CColoredPolygon2DRenderer::render() 
    {
        m_shader.bind();

        prepareBuffers();

        m_vao.bind();
            for( const SColoredPolygon2DRender_Batch& batch : m_vecBatches )
            {
                glDrawElements( batch.drawMode, batch.indexCount, GL_UNSIGNED_INT, ( void * )( sizeof( GLuint ) * batch.indexOffset ) );
            }
        m_vao.unbind();
    }

    void CColoredPolygon2DRenderer::render( const CFramebuffer& targetFramebuffer ) 
    {
        m_shader.bind();

        prepareBuffers();

        targetFramebuffer.bind();
        
        m_vao.bind();
            for( const SColoredPolygon2DRender_Batch& batch : m_vecBatches )
            {
                glDrawElements( batch.drawMode, batch.indexCount, GL_UNSIGNED_INT, ( void * )( sizeof( GLuint ) * batch.indexOffset ) );
            }
        m_vao.unbind();

        targetFramebuffer.unbind();
    }
    
} // namespace chestnut::engine
