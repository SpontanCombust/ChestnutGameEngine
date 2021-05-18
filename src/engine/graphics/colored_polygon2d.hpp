#ifndef __CHESTNUT_COLORED_POLYGON2D_H__
#define __CHESTNUT_COLORED_POLYGON2D_H__

#include "engine/libs.hpp"
#include "engine/maths/vector2.hpp"
#include "engine/maths/vector4.hpp"

namespace chestnut
{
    struct SColoredVertexBase
    {
        vec2f position;
        vec4f color;

        SColoredVertexBase() = default;
        SColoredVertexBase( vec2f position, vec4f color );
    };

    class CColoredPolygon2D
    {
    public:
        std::vector< SColoredVertexBase > vecVertices;
        std::vector< GLuint > vecIndices;

        void addVertex( vec2f position, vec4f color );
        void addVertex( vec2f position, float r, float g, float b, float a );
        void addVertex( vec2f position, char r, char g, char b, char a );
        // Throws an exception if any of indices doesn't correspond to a vertex
        void addIndices( GLuint i1, GLuint i2, GLuint i3 );

        bool isRenderable() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_COLORED_POLYGON2D_H__