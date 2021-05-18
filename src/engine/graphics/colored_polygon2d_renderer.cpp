#include "colored_polygon2d_renderer.hpp"

#include "engine/debug/debug.hpp"

#include <cassert>

#define INIT_POLYGON_VERTEX_CAPACITY 100
#define INIT_VERTEX_INDEX_CAPACITY 150

namespace chestnut
{
    CColoredPolygon2DRenderer::CColoredPolygon2DRenderer( const CShaderProgram& shader ) 
    {
        assert( shader.isValid() );
        m_shader = shader;

        assert( setShaderVariableNames( "avPos", "avColor", "avOrigin", "avTransl", "avScale", "avRot", "uView", "uProjection" ) );
        initBuffers();

        m_polygonVertexCapacity = 0;
        m_vertexIndexCapacity = 0;
        reserveBufferSpace( INIT_POLYGON_VERTEX_CAPACITY, INIT_VERTEX_INDEX_CAPACITY );
    }

    CColoredPolygon2DRenderer::~CColoredPolygon2DRenderer() 
    {
        glDeleteVertexArrays( 1, &m_vao );
        glDeleteBuffers( 1, &m_ebo );
        glDeleteBuffers( 1, &m_vbo );
    }

    bool CColoredPolygon2DRenderer::setShaderVariableNames( const std::string& attrVertPos,
                                                            const std::string& attrVertColor,
                                                            const std::string& attrVertOrigin,
                                                            const std::string& attrVertTransl,
                                                            const std::string& attrVertScale,
                                                            const std::string& attrVertRot,
                                                            const std::string& unifView,
                                                            const std::string& unifProjection )
    {
        m_attrVertPosLoc = m_shader.getAttributeLocation( attrVertPos );
        m_attrVertColorLoc = m_shader.getAttributeLocation( attrVertColor );
        m_attrVertOriginLoc = m_shader.getAttributeLocation( attrVertOrigin );
        m_attrVertTranslLoc = m_shader.getAttributeLocation( attrVertTransl );
        m_attrVertScaleLoc = m_shader.getAttributeLocation( attrVertScale );
        m_attrVertRotLoc = m_shader.getAttributeLocation( attrVertRot );

        m_unifViewLoc = m_shader.getUniformLocation( unifView );
        m_unifProjectionLoc = m_shader.getUniformLocation( unifProjection );

        if(    m_attrVertPosLoc     == -1
            || m_attrVertColorLoc   == -1
            || m_attrVertOriginLoc  == -1 
            || m_attrVertTranslLoc  == -1
            || m_attrVertScaleLoc   == -1
            || m_attrVertRotLoc     == -1
            || m_unifViewLoc        == -1
            || m_unifProjectionLoc  == -1 )
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
            glVertexAttribPointer( m_attrVertPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, position ) );

            glEnableVertexAttribArray( m_attrVertColorLoc );
            glVertexAttribPointer( m_attrVertColorLoc, 4, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, color ) );

            glEnableVertexAttribArray( m_attrVertOriginLoc );
            glVertexAttribPointer( m_attrVertOriginLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, origin ) );

            glEnableVertexAttribArray( m_attrVertTranslLoc );
            glVertexAttribPointer( m_attrVertTranslLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, translation ) );

            glEnableVertexAttribArray( m_attrVertScaleLoc );
            glVertexAttribPointer( m_attrVertScaleLoc, 2, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, scale ) );

            glEnableVertexAttribArray( m_attrVertRotLoc );
            glVertexAttribPointer( m_attrVertRotLoc, 1, GL_FLOAT, GL_FALSE, sizeof( SColoredVertex ), (void *)offsetof( SColoredVertex, rotation ) );

        glBindVertexArray(0);
    }

    void CColoredPolygon2DRenderer::bindShader() 
    {
        m_shader.bind();
    }

    void CColoredPolygon2DRenderer::unbindShader() 
    {
        m_shader.unbind();
    }

    void CColoredPolygon2DRenderer::setProjectionMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifProjectionLoc, mat );
    }

    void CColoredPolygon2DRenderer::setViewMatrix( const mat4f& mat ) 
    {
        m_shader.setMatrix4f( m_unifViewLoc, mat );
    }

    void CColoredPolygon2DRenderer::reserveBufferSpace( GLsizei targetPolygonVertexCapacity, GLsizei targetVertexIndexCapacity ) 
    {
        if( targetPolygonVertexCapacity > m_polygonVertexCapacity )
        {
            glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
            glBufferData( GL_ARRAY_BUFFER, sizeof( SColoredVertex ) * targetPolygonVertexCapacity, nullptr, GL_DYNAMIC_DRAW );
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
            LOG_CHANNEL( "COLORED_POLYGON2D_RENDERER", "Error occured while reserving buffer space: " << gluErrorString( err ) );
        }
    }

    void CColoredPolygon2DRenderer::clear() 
    {
        m_vecColoredVertices.clear();
        m_vecIndices.clear();
    }

    void CColoredPolygon2DRenderer::submitPolygon( const CColoredPolygon2D& polygon, const vec2f& translation, const vec2f& origin, const vec2f& scale, float rotation ) 
    {
        if( polygon.vecIndices.size() == 0 )
        {
            LOG_CHANNEL( "COLORED_POLYGON2D_RENDERER", "Polygon without indices cannot be used!" );
            return;
        }

        GLuint indexOffset = m_vecColoredVertices.size();

        SColoredVertex vert;
        for( const SColoredVertexBase& vertBase : polygon.vecVertices )
        {
            vert.position = vertBase.position;
            vert.color = vertBase.color;

            vert.origin = origin;
            vert.translation = translation;
            vert.scale = scale;
            vert.rotation = rotation;

            m_vecColoredVertices.push_back( vert );
        }

        for( const GLuint& index : polygon.vecIndices )
        {
            m_vecIndices.push_back( index + indexOffset );
        }
    }

    void CColoredPolygon2DRenderer::prepareBuffers() 
    {
        GLsizei vertexCount, indexCount;
        vertexCount = m_vecColoredVertices.size();
        indexCount = m_vecIndices.size();
        reserveBufferSpace( vertexCount, indexCount );

        glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( SColoredVertex ) * vertexCount, m_vecColoredVertices.data() );

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
        glBufferSubData( GL_ELEMENT_ARRAY_BUFFER, 0, sizeof( GLuint ) * indexCount, m_vecIndices.data() );
    }

    void CColoredPolygon2DRenderer::render() 
    {
        prepareBuffers();
        
        glBindVertexArray( m_vao );
            glDrawElements( GL_TRIANGLES, m_vecIndices.size(), GL_UNSIGNED_INT, 0 );
        glBindVertexArray(0);
    }
    
} // namespace chestnut
