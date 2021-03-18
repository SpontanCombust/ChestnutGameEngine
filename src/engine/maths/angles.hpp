#ifndef __CHESTNUT_ANGLES_H__
#define __CHESTNUT_ANGLES_H__

#include "vector.hpp"
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

    inline Vector2f angleToUnitVector2f( float angleRad )
    {
        return Vector2f( cos(angleRad), sin(angleRad) );
    }

    inline float unitVector2fToAngle( Vector2f v )
    {
        if( v.y >= 0.f )
            return atan2( v.y, v.x );
        else
            return 2 * CHESTNUT_PI + atan2( v.y, v.x );
    }

    inline float angleBetweenUnitVectors2f( Vector2f v1, Vector2f v2 )
    {
        return acos( vec2GetDotProduct( v1, v2 ) );
    }

    void rotateUnitVector2f( Vector2f& v, float angleRad );

} // namespace chestnut

#endif // __CHESTNUT_ANGLES_H__