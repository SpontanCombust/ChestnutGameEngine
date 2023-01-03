#pragma once


namespace chestnut::engine
{
    struct SRectangle
    {
        float x, y, w, h;

        SRectangle() : x(0), y(0), w(0), h(0) {}
        SRectangle( float _x, float _y, float _w, float _h ) : x(_x), y(_y), w(_w), h(_h) {}
    };

    inline bool operator==(const SRectangle& r1, const SRectangle& r2)
    {
        return r1.x == r2.x
            && r1.y == r2.y
            && r1.w == r2.w
            && r1.h == r2.h;
    } 

    inline bool operator!=(const SRectangle& r1, const SRectangle& r2)
    {
        return !(r1 == r2);
    } 

} // namespace chestnut::engine

