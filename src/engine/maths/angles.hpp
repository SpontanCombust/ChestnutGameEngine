#ifndef __CHESTNUT_ANGLES_H__
#define __CHESTNUT_ANGLES_H__

#include "vector2.hpp"
#include "engine/constants.hpp"

#include <cmath>

namespace chestnut
{
    inline float radiansToDegrees( float rad )
    {
        return rad * 180.f / CHESTNUT_PI;
    }

    inline float degreesToRadians( float deg )
    {
        return deg * CHESTNUT_PI / 180.f;
    }

    inline vec2f angleToUnitVec2f( float angleRad )
    {
        return vec2f( cos(angleRad), sin(angleRad) );
    }

    inline float unitVec2fToAngle( vec2f v )
    {
        if( v.y >= 0.f )
            return atan2( v.y, v.x );
        else
            return 2 * CHESTNUT_PI + atan2( v.y, v.x );
    }

    inline float angleBetweenUnitVecs2f( vec2f v1, vec2f v2 )
    {
        return acos( vec2DotProduct( v1, v2 ) );
    }

    void rotateUnitVec2f( vec2f& v, float angleRad );

} // namespace chestnut

#endif // __CHESTNUT_ANGLES_H__