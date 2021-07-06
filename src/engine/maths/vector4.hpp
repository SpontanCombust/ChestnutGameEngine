#ifndef __CHESTNUT_VECTOR4_H__
#define __CHESTNUT_VECTOR4_H__

#include "vector.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector<T,4>
    {
        T x, y, z, w;
        
        Vector();
        Vector( T init );
        Vector( T _x, T _y, T _z, T _w );

        T *data();
        const T *data() const;

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
    };


    using vec4f = Vector<float,4>;

} // namespace chestnut


#include "vector4.tpp"


#endif // __CHESTNUT_VECTOR4_H__