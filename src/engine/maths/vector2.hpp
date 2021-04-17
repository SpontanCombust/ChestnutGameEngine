#ifndef __CHESTNUT_VECTOR2_H__
#define __CHESTNUT_VECTOR2_H__

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector2
    {
        T x, y;

        Vector2();
        Vector2( T _x, T _y );

        std::string toString() const;

        template< typename U >
        operator Vector2<U>() const;
    };


    // predefined vectors //
    typedef Vector2<float> vec2f;
    typedef Vector2<int> vec2i;


    template< typename T >
    T vec2Magnitude( const Vector2<T>& v );


    template< typename T >
    Vector2<T> vec2Normalized( const Vector2<T>& v );


    template< typename T >
    Vector2<T> vec2Negated( const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator-( const Vector2<T>& v );


    template< typename T >
    Vector2<T> vec2Sum( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    Vector2<T> operator+( const Vector2<T>& v1, const Vector2<T>& v2 );


    template< typename T >
    Vector2<T> vec2Difference( const Vector2<T>& v1, const Vector2<T>& v2 );

    template<typename T>
    Vector2<T> operator-( const Vector2<T>& v1, const Vector2<T>& v2 );


    template< typename T >
    Vector2<T> vec2Scaled( const Vector2<T>& v, T s );

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s );


    template< typename T >
    T vec2DotProduct( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    T operator*( Vector2<T> v1, Vector2<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product

} // namespace chestnut


#include "vector2.tpp"


#endif // __CHESTNUT_VECTOR2_H__
