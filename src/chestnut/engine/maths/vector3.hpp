#ifndef __CHESTNUT_ENGINE_VECTOR3_H__
#define __CHESTNUT_ENGINE_VECTOR3_H__

#include "vector.hpp"
#include "vector2.hpp"

namespace chestnut
{
    template< typename T >
    struct Vector<T,3>
    {
        T x, y, z;

        Vector();
        Vector( T init );
        Vector( T _x, T _y, T _z );

        T *data();
        const T *data() const;

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
    };


    // predefined vectors //
    using vec3f = Vector<float,3>;


    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,2>& v1, const Vector<T,2>& v2 );

    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,3>& v1, const Vector<T,3>& v2 );

} // namespace chestnut


#include "vector3.tpp"


#endif // __CHESTNUT_ENGINE_VECTOR3_H__