#include "colored_polygon2d.hpp"

#include "engine/misc/exception.hpp"

namespace chestnut
{    
    SColoredVertexBase::SColoredVertexBase( vec2f position, vec4f color ) 
    {
        this->position = position;
        this->color = color;
    }

    void CColoredPolygon2D::addVertex( vec2f position, vec4f color ) 
    {
        vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addVertex( vec2f position, float r, float g, float b, float a ) 
    {
        vec4f color = { r, g, b, a };
        vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addVertex( vec2f position, char r, char g, char b, char a ) 
    {
        vec4f color = { (float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255 };
        vecVertices.emplace_back( position, color );
    }

    void CColoredPolygon2D::addIndices( GLuint i1, GLuint i2, GLuint i3 ) 
    {
        size_t size = vecVertices.size();
        if( i1 >= size || i2 >= size || i3 >= size )
        {
            throw ChestnutException( "Vertex index invalid!" );
        }

        vecIndices.push_back(i1);
        vecIndices.push_back(i2);
        vecIndices.push_back(i3);
    }

    bool CColoredPolygon2D::isRenderable() const
    {
        size_t size = vecIndices.size();
        if( size % 3 == 0 && size >= 3 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace chestnut
