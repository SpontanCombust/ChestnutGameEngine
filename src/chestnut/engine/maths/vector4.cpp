#include "vector4.hpp"

namespace chestnut::engine
{
    template<>
    struct Vector<float,4>;



    template<>
    float vecMagnitude( const Vector<float,4>& v );


    template<>
    Vector<float,4> vecNormalized( const Vector<float,4>& v );


    template<>
    Vector<float,4> vecNegated( const Vector<float,4>& v );

    template<>
    Vector<float,4> operator-( const Vector<float,4>& v );


    template<>
    Vector<float,4> vecSum( const Vector<float,4>& v1, const Vector<float,4>& v2 );

    template<>
    Vector<float,4> operator+( const Vector<float,4>& v1, const Vector<float,4>& v2 );


    template<>
    Vector<float,4> vecDifference( const Vector<float,4>& v1, const Vector<float,4>& v2 );

    template<>
    Vector<float,4> operator-( const Vector<float,4>& v1, const Vector<float,4>& v2 );


    template<>
    Vector<float,4> vecScalarProduct( const Vector<float,4>& v, float s );

    template<>
    Vector<float,4> operator*( float s, const Vector<float,4>& v );

    template<>
    Vector<float,4> operator*( const Vector<float,4>& v, float s );


    template<>
    float vecDotProduct( const Vector<float,4>& v1, const Vector<float,4>& v2 );


    template<>
    Vector<float,4> vecComponentProduct( const Vector<float,4>& v1, const Vector<float,4>& v2 );

    template<>
    Vector<float,4> operator*( const Vector<float,4>& v1, const Vector<float,4>& v2 );


    template<>
    Vector<float,4> vecComponentQuotient( const Vector<float,4>& v1, const Vector<float,4>& v2 );

    template<>
    Vector<float,4> operator/( const Vector<float,4>& v1, const Vector<float,4>& v2 );


    template<>
    std::string vecToString( const Vector<float,4>& v );

} // namespace chestnut::engine
