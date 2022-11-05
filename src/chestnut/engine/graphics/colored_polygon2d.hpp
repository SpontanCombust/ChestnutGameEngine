#pragma once


#include "chestnut/engine/macros.hpp"
#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/maths/vector4.hpp"

#include <glad/glad.h>

#include <vector>

namespace chestnut::engine
{
    struct SVertex2D
    {
        vec2f pos;

        SVertex2D( vec2f _pos )
        {
            pos = _pos;
        }
    };

    struct SColoredVertex2D
    {
        vec2f pos;
        vec4f color;

        SColoredVertex2D( vec2f _pos, vec4f _color )
        {
            pos = _pos;
            color = _color;
        }
    };


    struct SColoredPolygon2D
    {
        std::vector< SVertex2D > vecVertices;
        std::vector< GLuint > vecIndices;
        vec4f color;
        GLenum drawMode;

        SColoredPolygon2D()
        {
            color = vec4f(1.f);
            drawMode = GL_TRIANGLES;
        }
    };

    struct SMulticoloredPolygon2D
    {
        std::vector< SColoredVertex2D > vecVertices;
        std::vector< GLuint > vecIndices;
        GLenum drawMode;

        SMulticoloredPolygon2D()
        {
            drawMode = GL_TRIANGLES;
        }
    };


    namespace colored_polygon_templates
    {
        SColoredPolygon2D CHESTNUT_API coloredPolygonTriangle( float a );

        SColoredPolygon2D CHESTNUT_API coloredPolygonTriangle( float a, float h );

        SColoredPolygon2D CHESTNUT_API coloredPolygonSquare( float a );

        SColoredPolygon2D CHESTNUT_API coloredPolygonRectangle( float a, float b );

        SColoredPolygon2D CHESTNUT_API coloredPolygonCircle( float r, unsigned int segments );

    } // namespace coloredPolygonTemplates
    

} // namespace chestnut::engine

