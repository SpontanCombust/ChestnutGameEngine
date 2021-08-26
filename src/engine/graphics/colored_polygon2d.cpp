#include "colored_polygon2d.hpp"

#include "../misc/exception.hpp"

namespace chestnut
{    
    SColoredVertex::SColoredVertex( vec2f position, vec4f color ) 
    {
        this->position = position;
        this->color = color;
    }



    void CColoredPolygon2D::addVertex( vec2f position, vec4f color ) 
    {
        m_vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addVertex( vec2f position, float r, float g, float b, float a ) 
    {
        vec4f color = { r, g, b, a };
        m_vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addVertex( vec2f position, char r, char g, char b, char a ) 
    {
        vec4f color = { (float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255 };
        m_vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addIndices( GLuint i1, GLuint i2, GLuint i3 ) 
    {
        size_t size = m_vecVertices.size();
        if( i1 >= size || i2 >= size || i3 >= size )
        {
            throw ChestnutException( "Vertex index invalid!" );
        }

        m_vecIndices.push_back(i1);
        m_vecIndices.push_back(i2);
        m_vecIndices.push_back(i3);
    }

    bool CColoredPolygon2D::isRenderable() const
    {
        if( m_vecIndices.size() >= 3 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    const std::vector< SColoredVertex >& CColoredPolygon2D::getVertices() const
    {
        return m_vecVertices;
    }

    const std::vector< GLuint >& CColoredPolygon2D::getIndices() const
    {
        return m_vecIndices;
    }

} // namespace chestnut
