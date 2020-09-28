#ifndef __CHESTNUT_VECTOR_H__
#define __CHESTNUT_VECTOR_H__

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector2
    {
        T x, y;

        Vector2() : x(0), y(0) {}
        Vector2( T _x, T _y ) : x(_x), y(_y) {} 

        T getMagnitude() const;

        void normalize();

        void negate();

        void add( const Vector2& other );
        void operator+=( const Vector2& other );

        void subtract( const Vector2& other );
        void operator-=( const Vector2& other );

        void multiplyByScalar( const T s );
        void operator*=( const T s );

        T multiplyByVecDot( const Vector2<T>& other ) const;

        std::string to_string();
    };


    template< typename T >
    Vector2<T> vec2GetNormalized( const Vector2<T>& v );


    template< typename T >
    Vector2<T> vec2GetNegated( const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator-( const Vector2<T>& v );


    template< typename T >
    Vector2<T> vec2GetSum( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    Vector2<T> operator+( const Vector2<T>& v1, const Vector2<T>& v2 );


    template< typename T >
    Vector2<T> vec2GetDifference( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    Vector2<T> operator-( const Vector2<T>& v1, const Vector2<T>& v2 );


    template< typename T >
    Vector2<T> vec2GetScaled( const Vector2<T>& v, T s );

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s );


    template< typename T >
    T vec2GetDotProduct( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    T operator*( Vector2<T> v1, Vector2<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product


    // predefined vectors //
    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;

} // namespace chestnut

#endif // __CHESTNUT_VECTOR_H__
