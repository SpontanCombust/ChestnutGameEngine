#ifndef __CHESTNUT_VECTOR3_H__
#define __CHESTNUT_VECTOR3_H__

#include "vector2.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector3
    {
        T x, y, z;

        Vector3();
        Vector3( T _x, T _y, T _z );

        std::string toString() const;

        template< typename U >
        operator Vector3<U>() const;
    };


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
    Vector3<T> vec3Scaled( const Vector3<T>& v, T s );

    template< typename T >
    Vector3<T> operator*( T s, const Vector3<T>& v );

    template< typename T >
    Vector3<T> operator*( const Vector3<T>& v, T s );


    template< typename T >
    T vec3DotProduct( const Vector3<T>& v1, const Vector3<T>& v2 );

    template< typename T >
    T operator*( Vector3<T> v1, Vector3<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product


    template< typename T >
    Vector2<T> vec3ToVec2( const Vector3<T>& v );

    template< typename T >
    Vector3<T> vec2ToVec3( const Vector2<T>& v );

} // namespace chestnut


#include "vector3.tpp"


#endif // __CHESTNUT_VECTOR3_H__
