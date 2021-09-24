#ifndef __CHESTNUT_ENGINE_RECTANGLE_H__
#define __CHESTNUT_ENGINE_RECTANGLE_H__

namespace chestnut
{
    struct SRectangle
    {
        float x, y, w, h;

        SRectangle() : x(0), y(0), w(0), h(0) {}
        SRectangle( float _x, float _y, float _w, float _h ) : x(_x), y(_y), w(_w), h(_h) {}
    };

} // namespace chestnut

#endif // __CHESTNUT_ENGINE_RECTANGLE_H__