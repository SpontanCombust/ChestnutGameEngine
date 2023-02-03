#include "chestnut/engine/maths/vector3.hpp"

namespace chestnut::engine
{
    template
    struct Vector<float,3>;



    template
    float vecMagnitude( const Vector<float,3>& v );

    template
    Vector<float,3> vecNormalized( const Vector<float,3>& v );

    template
    Vector<float,3> vecNegated( const Vector<float,3>& v );

    template
    Vector<float,3> vecSum( const Vector<float,3>& v1, const Vector<float,3>& v2 );

    template
    Vector<float,3> vecDifference( const Vector<float,3>& v1, const Vector<float,3>& v2 );

    template
    Vector<float,3> vecScalarProduct( const Vector<float,3>& v, float s );

    template
    Vector<float,3> vecScalarQuotient( const Vector<float,3>& v, float s );

    template
    float vecDotProduct( const Vector<float,3>& v1, const Vector<float,3>& v2 );

    template
    Vector<float,3> vecComponentProduct( const Vector<float,3>& v1, const Vector<float,3>& v2 );

    template
    Vector<float,3> vecComponentQuotient( const Vector<float,3>& v1, const Vector<float,3>& v2 );

    template
    std::string vecToString( const Vector<float,3>& v );

    template
    Vector<float,3> vecCrossProduct( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<float,3> vecCrossProduct( const Vector<float,3>& v1, const Vector<float,3>& v2 );

} // namespace chestnut::engine
