#ifndef __CHESTNUT_VECTOR3_H__
#define __CHESTNUT_VECTOR3_H__

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector2;

    template< typename T >
    struct Vector4;

    template< typename T >
    struct Matrix4;


    template< typename T >
    struct Vector3
    {
        T x, y, z;

        Vector3();
        Vector3( T _x, T _y, T _z );

        Vector3& operator+=( const Vector3& v );
        Vector3& operator-=( const Vector3& v );
        Vector3& operator*=( T s );

        std::string toString() const;

        template< typename U >
        operator Vector3<U>() const;

        operator Vector2<T>() const;
        operator Vector4<T>() const;
    };


    template< typename T >
    using vec3 = Vector3<T>;

    // predefined vectors //
    typedef Vector3<float> vec3f;
    typedef Vector3<int> vec3i;


    template< typename T >
    T vec3Magnitude( const Vector3<T>& v );


    template< typename T >
    Vector3<T> vec3Normalized( const Vector3<T>& v );


    template< typename T >
    Vector3<T> vec3Negated( const Vector3<T>& v );

    template< typename T >
    Vector3<T> operator-( const Vector3<T>& v );


    template< typename T >
    Vector3<T> vec3Sum( const Vector3<T>& v1, const Vector3<T>& v2 );

    template< typename T >
    Vector3<T> operator+( const Vector3<T>& v1, const Vector3<T>& v2 );


    template< typename T >
    Vector3<T> vec3Difference( const Vector3<T>& v1, const Vector3<T>& v2 );

    template<typename T>
    Vector3<T> operator-( const Vector3<T>& v1, const Vector3<T>& v2 );


    template< typename T >
    Vector3<T> vec3ScalarProduct( const Vector3<T>& v, T s );

    template< typename T >
    Vector3<T> operator*( T s, const Vector3<T>& v );

    template< typename T >
    Vector3<T> operator*( const Vector3<T>& v, T s );


    template< typename T >
    T vec3DotProduct( const Vector3<T>& v1, const Vector3<T>& v2 );

    template< typename T >
    Vector3<T> vec3CrossProduct( const Vector3<T>& v1, const Vector3<T>& v2 );

    template< typename T >
    T operator*( Vector3<T> v1, Vector3<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product


    template< typename T >
    Vector3<T> vec3LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector3<T>& v );

    template< typename T >
    Vector3<T> operator*( const Matrix4<T>& lhs, const Vector3<T>& rhs );

    template< typename T >
    Vector3<T> vec3Translate( const Vector3<T>& v, T tx, T ty, T tz );

    template< typename T >
    Vector3<T> vec3Scale( const Vector3<T>& v, T sx, T sy, T sz );

    template< typename T >
    Vector3<T> vec3Rotate( const Vector3<T>& v, Vector3<T> axis, double angleRad );


    template< typename T >
    Vector2<T> vec3ToVec2( const Vector3<T>& v );

    template< typename T >
    Vector4<T> vec3ToVec4( const Vector3<T>& v, T w = 1.0 );

} // namespace chestnut


#include "vector3.tpp"


#endif // __CHESTNUT_VECTOR3_H__
