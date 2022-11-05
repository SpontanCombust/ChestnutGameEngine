#pragma once


#include "chestnut/engine/maths/vector2.hpp"
#include "chestnut/engine/constants.hpp"

#include <cmath>

namespace chestnut::engine
{
    struct SEulerAngles
    {
        float yaw;
        float pitch;
        float roll;

        SEulerAngles() : yaw(0.0f), pitch(0.0f), roll(0.0f) {}
    };



    inline constexpr float radiansToDegrees( float rad )
    {
        return rad * 180.f / (float)CHESTNUT_PI;
    }

    inline constexpr float degreesToRadians( float deg )
    {
        return deg * (float)CHESTNUT_PI / 180.f;
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
            return 2 * (float)CHESTNUT_PI + atan2( v.y, v.x );
    }

    inline float angleBetweenUnitVecs2f( vec2f v1, vec2f v2 )
    {
        return acos( vecDotProduct( v1, v2 ) );
    }

    inline void rotateUnitVec2f( vec2f& v, float angleRad )
    {
        float sine = sin(angleRad), cosine = cos(angleRad);
        v.x = v.x * cosine - v.y * sine;
        v.y = v.x * sine + v.y * cosine;
    }

} // namespace chestnut::engine

