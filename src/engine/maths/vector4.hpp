#ifndef __CHESTNUT_VECTOR4_H__
#define __CHESTNUT_VECTOR4_H__

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector2;

    template< typename T >
    struct Vector3;

    template< typename T >
    struct Matrix4;


    template< typename T >
    struct Vector4
    {
        T x, y, z, w;

        Vector4();
        Vector4( T _x, T _y, T _z, T _w );

        Vector4& operator+=( const Vector4& v );
        Vector4& operator-=( const Vector4& v );
        Vector4& operator*=( T s );

        std::string toString() const;

        template< typename U >
        operator Vector4<U>() const;

        operator Vector2<T>() const;
        operator Vector3<T>() const;
    };


    template< typename T >
    using vec4 = Vector4<T>;

    typedef Vector4<float> vec4f;


    template< typename T >
    Vector4<T> vec4Negated( const Vector4<T>& v );

    template< typename T >
    Vector4<T> operator-( const Vector4<T>& v );


    template< typename T >
    Vector4<T> vec4Sum( const Vector4<T>& v1, const Vector4<T>& v2 );

    template< typename T >
    Vector4<T> operator+( const Vector4<T>& v1, const Vector4<T>& v2 );


    template< typename T >
    Vector4<T> vec4Difference( const Vector4<T>& v1, const Vector4<T>& v2 );

    template<typename T>
    Vector4<T> operator-( const Vector4<T>& v1, const Vector4<T>& v2 );


    template< typename T >
    Vector4<T> vec4ScalarProduct( const Vector4<T>& v, T s );

    template< typename T >
    Vector4<T> operator*( T s, const Vector4<T>& v );

    template< typename T >
    Vector4<T> operator*( const Vector4<T>& v, T s );


    template< typename T >
    Vector4<T> vec4LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector4<T>& v );

    template< typename T >
    Vector4<T> operator*( const Matrix4<T>& m, const Vector4<T>& v );


    template< typename T >
    Vector2<T> vec4ToVec2( const Vector4<T>& v );

    template< typename T >
    Vector3<T> vec4ToVec3( const Vector4<T>& v );

} // namespace chestnut


#include "vector4.tpp"


#endif // __CHESTNUT_VECTOR4_H__