#include "vector2.hpp"

namespace chestnut
{
    template struct Vector<float,2>;
    template struct Vector<int,2>;


    template
    float vecMagnitude( const Vector<float,2>& v );

    template
    int vecMagnitude( const Vector<int,2>& v );


    template
    Vector<float,2> vecNormalized( const Vector<float,2>& v );


    template
    Vector<float,2> vecNegated( const Vector<float,2>& v );

    template
    Vector<int,2> vecNegated( const Vector<int,2>& v );

    template
    Vector<float,2> operator-( const Vector<float,2>& v );

    template
    Vector<int,2> operator-( const Vector<int,2>& v );


    template
    Vector<float,2> vecSum( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> vecSum( const Vector<int,2>& v1, const Vector<int,2>& v2 );

    template
    Vector<float,2> operator+( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> operator+( const Vector<int,2>& v1, const Vector<int,2>& v2 );


    template
    Vector<float,2> vecDifference( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> vecDifference( const Vector<int,2>& v1, const Vector<int,2>& v2 );

    template
    Vector<float,2> operator-( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> operator-( const Vector<int,2>& v1, const Vector<int,2>& v2 );


    template
    Vector<float,2> vecScalarProduct( const Vector<float,2>& v, float s );

    template
    Vector<int,2> vecScalarProduct( const Vector<int,2>& v, int s );

    template
    Vector<float,2> operator*( float s, const Vector<float,2>& v );

    template
    Vector<int,2> operator*( int s, const Vector<int,2>& v );

    template
    Vector<float,2> operator*( const Vector<float,2>& v, float s );

    template
    Vector<int,2> operator*( const Vector<int,2>& v, int s );


    template
    float vecDotProduct( const Vector<float,2>& v1, const Vector<float,2>& v2 );


    template
    Vector<float,2> vecComponentProduct( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> vecComponentProduct( const Vector<int,2>& v1, const Vector<int,2>& v2 );

    template
    Vector<float,2> operator*( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> operator*( const Vector<int,2>& v1, const Vector<int,2>& v2 );


    template
    Vector<float,2> vecComponentQuotient( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> vecComponentQuotient( const Vector<int,2>& v1, const Vector<int,2>& v2 );

    template
    Vector<float,2> operator/( const Vector<float,2>& v1, const Vector<float,2>& v2 );

    template
    Vector<int,2> operator/( const Vector<int,2>& v1, const Vector<int,2>& v2 );


    template
    std::string vecToString( const Vector<float,2>& v );

    template
    std::string vecToString( const Vector<int,2>& v );

} // namespace chestnut
