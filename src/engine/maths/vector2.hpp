#ifndef __CHESTNUT_VECTOR2_H__
#define __CHESTNUT_VECTOR2_H__

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector3;

    template< typename T >
    struct Vector4;

    template< typename T >
    struct Matrix4;


    template< typename T >
    struct Vector2
    {
        T x, y;

        Vector2();
        Vector2( T _x, T _y );

        Vector2& operator+=( const Vector2& v );
        Vector2& operator-=( const Vector2& v );
        Vector2& operator*=( T s );

        std::string toString() const;

        template< typename U >
        operator Vector2<U>() const;

        operator Vector3<T>() const;
        operator Vector4<T>() const;
    };


    template< typename T >
    using vec2 = Vector2<T>;
    
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
    Vector2<T> vec2ScalarProduct( const Vector2<T>& v, T s );

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s );


    template< typename T >
    T vec2DotProduct( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    Vector3<T> vec2CrossProduct( const Vector2<T>& v1, const Vector2<T>& v2 );

    template< typename T >
    T operator*( Vector2<T> v1, Vector2<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product


    template< typename T >
    Vector2<T> vec2LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector2<T>& v );

    template< typename T >
    Vector2<T> operator*( const Matrix4<T>& lhs, const Vector2<T>& rhs );

    template< typename T >
    Vector2<T> vec2Translate( const Vector2<T>& v, T tx, T ty );

    template< typename T >
    Vector2<T> vec2Scale( const Vector2<T>& v, T sx, T sy );

    template< typename T >
    Vector2<T> vec2Rotate( const Vector2<T>& v, double angleRad );


    template< typename T >
    Vector3<T> vec2ToVec3( const Vector2<T>& v, T z = 0.0 );

    template< typename T >
    Vector4<T> vec2ToVec4( const Vector2<T>& v, T z = 0.0, T w = 1.0 );

} // namespace chestnut


#include "vector2.tpp"


#endif // __CHESTNUT_VECTOR2_H__
