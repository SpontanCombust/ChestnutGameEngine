#include "colored_polygon2d.hpp"

#include "../constants.hpp"
#include "../maths/vector_transform.hpp"

namespace chestnut::engine
{    
    SVertex2D::SVertex2D( vec2f _pos ) 
    {
        pos = _pos;
    }

    SColoredVertex2D::SColoredVertex2D( vec2f _pos, vec4f _color ) 
    {
        pos = _pos;
        color = _color;
    }

    SColoredPolygon2D::SColoredPolygon2D() 
    {
        color = vec4f(1.f);
        drawMode = GL_TRIANGLES;
    }

    SMulticoloredPolygon2D::SMulticoloredPolygon2D() 
    {
        drawMode = GL_TRIANGLES;
    }



    namespace colored_polygon_templates
    {
        SColoredPolygon2D coloredPolygonTriangle( float a )
        {
            SColoredPolygon2D poly;
 
            vec2f v{ 0.f, -2.f * a / 3.f };
            poly.vecVertices.push_back(v);
            vecRotate( v, 2 * CHESTNUT_PI / 3.f );
            poly.vecVertices.push_back(v);
            vecRotate( v, 2 * CHESTNUT_PI / 3.f );
            poly.vecVertices.push_back(v);
            
            poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 2} );

            return poly;
        }

        SColoredPolygon2D coloredPolygonTriangle( float a, float h )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ 0.f, -2.f * h / 3.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, h / 3.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, h / 3.f } );

            poly.vecIndices.insert( poly.vecIndices.end(), { 0, 1, 2 } );

            return poly;
        }

        SColoredPolygon2D coloredPolygonSquare( float a )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ -a / 2.f, -a / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, -a / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, a / 2.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, a / 2.f } );
            
            poly.vecIndices.insert( poly.vecIndices.end(), { 0, 1, 2, 2, 3, 0 } );

            return poly;
        }

        SColoredPolygon2D coloredPolygonRectangle( float a, float b )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ -a / 2.f, -b / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, -b / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, b / 2.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, b / 2.f } );
            
            poly.vecIndices.insert( poly.vecIndices.end(), { 0, 1, 2, 2, 3, 0 } );

            return poly;
        }

        SColoredPolygon2D coloredPolygonCircle( float r, unsigned int segments )
        {
            if( segments < 3 )
            {
                segments = 3;
            }

            float rot = 2 * CHESTNUT_PI / (float)segments;

            SColoredPolygon2D poly;
            poly.vecVertices.push_back( vec2f{ 0.f, 0.f } );

            vec2f v { r, 0.f };
            poly.vecVertices.push_back(v);

            unsigned int i;
            for (i = 2; i < segments + 1; i++)
            {
                vecRotate( v, rot );
                poly.vecVertices.push_back(v);
                poly.vecIndices.insert( poly.vecIndices.end(), { 0, i - 1, i } );
            }
            
            poly.vecIndices.insert( poly.vecIndices.end(), { 0, i - 1, 1 } );


            return poly;
        }

    } // namespace colored_polygon_templates
    
} // namespace chestnut::engine
