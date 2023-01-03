#include "chestnut/engine/graphics/colored_polygon2d.hpp"

#include "chestnut/engine/constants.hpp"
#include "chestnut/engine/maths/vector_transform.hpp"

namespace chestnut::engine
{    
    namespace colored_polygon_templates
    {
        SColoredPolygon2D coloredPolygonTriangle( float a, bool outlineOnly )
        {
            SColoredPolygon2D poly;
 
            vec2f v{ 0.f, -2.f * a / 3.f };
            poly.vecVertices.push_back(v);
            vecRotate( v, 2 * CHESTNUT_PI_F / 3.f );
            poly.vecVertices.push_back(v);
            vecRotate( v, 2 * CHESTNUT_PI_F / 3.f );
            poly.vecVertices.push_back(v);
            
            if(outlineOnly)
            {
                poly.drawMode = GL_LINES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 1, 2, 2, 0} );
            }
            else
            {
                poly.drawMode = GL_TRIANGLES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 2} );
            }

            return poly;
        }

        SColoredPolygon2D coloredPolygonTriangle( float a, float h, bool outlineOnly )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ 0.f, -2.f * h / 3.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, h / 3.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, h / 3.f } );

            if(outlineOnly)
            {
                poly.drawMode = GL_LINES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 1, 2, 2, 0} );
            }
            else
            {
                poly.drawMode = GL_TRIANGLES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 2} );
            }

            return poly;
        }

        SColoredPolygon2D coloredPolygonSquare( float a, bool outlineOnly )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ -a / 2.f, -a / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, -a / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, a / 2.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, a / 2.f } );

            if(outlineOnly)
            {
                poly.drawMode = GL_LINES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 1, 2, 2, 3, 3, 0} );
            }
            else
            {
                poly.drawMode = GL_TRIANGLES;
                poly.vecIndices.insert( poly.vecIndices.end(), { 0, 1, 2, 2, 3, 0 } );
            }

            return poly;
        }

        SColoredPolygon2D coloredPolygonRectangle( float a, float b, bool outlineOnly )
        {
            SColoredPolygon2D poly;

            poly.vecVertices.push_back( vec2f{ -a / 2.f, -b / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, -b / 2.f } );
            poly.vecVertices.push_back( vec2f{ a / 2.f, b / 2.f } );
            poly.vecVertices.push_back( vec2f{ -a / 2.f, b / 2.f } );
            
            if(outlineOnly)
            {
                poly.drawMode = GL_LINES;
                poly.vecIndices.insert( poly.vecIndices.end(), {0, 1, 1, 2, 2, 3, 3, 0} );
            }
            else
            {
                poly.drawMode = GL_TRIANGLES;
                poly.vecIndices.insert( poly.vecIndices.end(), { 0, 1, 2, 2, 3, 0 } );
            }

            return poly;
        }

        SColoredPolygon2D coloredPolygonCircle( float r, unsigned int segments, bool outlineOnly )
        {
            if( segments < 3 )
            {
                segments = 3;
            }

            float rot = 2 * CHESTNUT_PI_F / (float)segments;

            SColoredPolygon2D poly;
            vec2f v { r, 0.f };

            if(outlineOnly)
            {
                poly.drawMode = GL_LINES;
                
                poly.vecVertices.push_back(v);

                unsigned int i;
                for (i = 1; i < segments + 1; i++)
                {
                    vecRotate( v, rot );
                    poly.vecVertices.push_back(v);
                    poly.vecIndices.insert( poly.vecIndices.end(), {i - 1, i} );
                }
                
                poly.vecIndices.insert( poly.vecIndices.end(), {i - 1, 0} );
            }
            else
            {
                poly.drawMode = GL_TRIANGLES;
                
                poly.vecVertices.push_back( vec2f{ 0.f, 0.f } );
                poly.vecVertices.push_back(v);

                unsigned int i;
                for (i = 2; i < segments + 1; i++)
                {
                    vecRotate( v, rot );
                    poly.vecVertices.push_back(v);
                    poly.vecIndices.insert( poly.vecIndices.end(), { 0, i - 1, i } );
                }
                
                poly.vecIndices.insert( poly.vecIndices.end(), { 0, i - 1, 1 } );
            }

            return poly;
        }

    } // namespace colored_polygon_templates
    
} // namespace chestnut::engine
