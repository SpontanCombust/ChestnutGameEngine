#include "colored_polygon2d_renderer.hpp"

#include "../../debug/log.hpp"
#include "../../macros.hpp"

namespace chestnut::engine
{
    void CColoredPolygon2DRenderer::onInit() 
    {
        m_polygonVertexCapacity = 0;
        m_vertexIndexCapacity = 0;
        reserveBufferSpace( CHESTNUT_POLYGON_RENDERER_INIT_VERTEX_CAPACITY, CHESTNUT_POLYGON_RENDERER_INIT_INDEX_CAPACITY );
    }

    void CColoredPolygon2DRenderer::deleteBuffers() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    bool CColoredPolygon2DRenderer::setShaderVariableLocations()
    {
        m_attrVertPosLoc = m_shader.getAttributeLocation( "avPos" );
        m_attrVertColorLoc = m_shader.getAttributeLocation( "avColor" );
        m_attrVertTranslLoc = m_shader.getAttributeLocation( "avTransl" );
        m_attrVertScaleLoc = m_shader.getAttributeLocation( "avScale" );
        m_attrVertRotLoc = m_shader.getAttributeLocation( "avRot" );

        if(    m_attrVertPosLoc     == -1
            || m_attrVertColorLoc   == -1
            || m_attrVertTranslLoc  == -1
            || m_attrVertScaleLoc   == -1
            || m_attrVertRotLoc     == -1 )
        {
            return false;
        }

        return true;
    }

    void CColoredPolygon2DRenderer::initBuffers() 
    {
        glGenBuffers( 1, &m_vbo );
        glGenBuffers( 1, &m_ebo );
        glGenVertexArrays( 1, &m_vao );

        glBindVertexArray( m_vao );

            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );

            glEnableVertexAttribArray( m_attrVertPosLoc );
            glVertexAttribPointer( m_attrVertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredPolygon2DRender_Vertex ), (void *)offsetof( SColoredPolygon2DRender_Vertex, position ) );

            glEnableVertexAttribArray( m_attrVertColorLoc );
            glVertexAttribPointer( m_attrVertColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof( SColoredPolygon2DRender_Vertex ), (void *)offsetof( SColoredPolygon2DRender_Vertex, color ) );

            glEnableVertexAttribArray( m_attrVertTranslLoc );
            glVertexAttribPointer( m_attrVertTranslLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredPolygon2DRender_Vertex ), (void *)offsetof( SColoredPolygon2DRender_Vertex, translation ) );

            glEnableVertexAttribArray( m_attrVertScaleLoc );
            glVertexAttribPointer( m_attrVertScaleLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredPolygon2DRender_Vertex ), (void *)offsetof( SColoredPolygon2DRender_Vertex, scale ) );

            glEnableVertexAttribArray( m_attrVertRotLoc );
            glVertexAttribPointer( m_attrVertRotLoc, 1, GL_FLOAT, GL_FALSE, sizeof( SColoredPolygon2DRender_Vertex ), (void *)offsetof( SColoredPolygon2DRender_Vertex, rotation ) );

        glBindVertexArray(0);
    }

    void CColoredPolygon2DRenderer::reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity ) 
    {
        if( targetPolygonVertexCapacity > m_polygonVertexCapacity )
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferData( GL_ARRAY_BUFFER, sizeof( SColoredPolygon2DRender_Vertex ) * targetPolygonVertexCapacity, nullptr, GL_DYNAMIC_DRAW );
            m_polygonVertexCapacity = targetPolygonVertexCapacity;
        }
        if( targetVertexIndexCapacity > m_vertexIndexCapacity )
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_ebo );
            glBufferData( GL_ARRAY_BUFFER, sizeof( GLuint ) * targetVertexIndexCapacity, nullptr, GL_DYNAMIC_DRAW );
            m_vertexIndexCapacity = targetVertexIndexCapacity;
        }

        GLenum err = glGetError();
        if( err != GL_NO_ERROR )
        {
            LOG_ERROR( "Error occured while reserving buffer space: " << gluErrorString( err ) );
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
            // and a map to store the data for these modes, there's not an easy way of storing valid indices
            // if we can submit polygons with different drawing modes in random order
            // that's why here when we're going over every draw mode in the map we keep track of previously
            // checked vertex group index count and apply an offset to the next one to make these groups be contiguous in the EBO
            // and to not overwrite each other
            for( GLuint& index : vertexGroup.vecRenderIndices )
            {
                index += vertexOffset;
            }

            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferSubData( GL_ARRAY_BUFFER, sizeof( SColoredPolygon2DRender_Vertex ) * vertexOffset, sizeof( SColoredPolygon2DRender_Vertex ) * vertexCount, vertexGroup.vecRenderVertices.data() );

            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
            glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * indexOffset, sizeof( GLuint ) * indexCount, vertexGroup.vecRenderIndices.data() );


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
        prepareBuffers();

        glBindVertexArray( m_vao );
            for( const SColoredPolygon2DRender_Batch& batch : m_vecBatches )
            {
                glDrawElements( batch.drawMode, batch.indexCount, GL_UNSIGNED_INT, ( void * )( sizeof( GLuint ) * batch.indexOffset ) );
            }
        glBindVertexArray(0);
    }

    void CColoredPolygon2DRenderer::render( const CFramebuffer& targetFramebuffer ) 
    {
        prepareBuffers();

        targetFramebuffer.bind();
        
        glBindVertexArray( m_vao );
            for( const SColoredPolygon2DRender_Batch& batch : m_vecBatches )
            {
                glDrawElements( batch.drawMode, batch.indexCount, GL_UNSIGNED_INT, ( void * )( sizeof( GLuint ) * batch.indexOffset ) );
            }
        glBindVertexArray(0);

        targetFramebuffer.unbind();
    }
    
} // namespace chestnut::engine
