#include "colored_polygon2d.hpp"

#include "../misc/exception.hpp"

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

} // namespace chestnut::engine
