#include "angles.hpp"

namespace chestnut::engine
{
    void rotateUnitVec2f( vec2f& v, float angleRad )
    {
        float sine = sin(angleRad), cosine = cos(angleRad);
        v.x = v.x * cosine - v.y * sine;
        v.y = v.x * sine + v.y * cosine;
    }
    
} // namespace chestnut::engine
