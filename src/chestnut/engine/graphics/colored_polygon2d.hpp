#ifndef __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__
#define __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__

#include "../maths/vector2.hpp"
#include "../maths/vector4.hpp"

#include <GL/glew.h>

#include <vector>

namespace chestnut::engine
{
    struct SVertex2D
    {
        vec2f pos;

        SVertex2D( vec2f _pos );
    };

    struct SColoredVertex2D
    {
        vec2f pos;
        vec4f color;

        SColoredVertex2D( vec2f _pos, vec4f _color );
    };


    struct SColoredPolygon2D
    {
        std::vector< SVertex2D > vecVertices;
        std::vector< GLuint > vecIndices;
        vec4f color;
        GLenum drawMode;

        SColoredPolygon2D();
    };

    struct SMulticoloredPolygon2D
    {
        std::vector< SColoredVertex2D > vecVertices;
        std::vector< GLuint > vecIndices;
        GLenum drawMode;

        SMulticoloredPolygon2D();
    };

} // namespace chestnut::engine

#endif // __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__