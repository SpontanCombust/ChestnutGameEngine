#ifndef __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__
#define __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__

#include "../maths/vector2.hpp"
#include "../maths/vector4.hpp"

#include <GL/glew.h>

namespace chestnut
{
    struct SColoredVertex
    {
        vec2f position;
        vec4f color;

        SColoredVertex() = default;
        SColoredVertex( vec2f position, vec4f color );
    };

    class CColoredPolygon2D
    {
    private:
        std::vector< SColoredVertex > m_vecVertices;
        std::vector< GLuint > m_vecIndices;

    public:
        void addVertex( vec2f position, vec4f color );
        void addVertex( vec2f position, float r, float g, float b, float a );
        void addVertex( vec2f position, char r, char g, char b, char a );
        // Throws an exception if any of indices doesn't correspond to a vertex
        void addIndices( GLuint i1, GLuint i2, GLuint i3 );

        bool isRenderable() const;

        const std::vector< SColoredVertex >& getVertices() const;
        const std::vector< GLuint >& getIndices() const;
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_COLORED_POLYGON2D_H__