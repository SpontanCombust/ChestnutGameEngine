#pragma once


#include "vector.hpp"

#include <string>

namespace chestnut::engine
{
    template< typename T >
    struct Vector<T,4>
    {
        T x, y, z, w;
        
        Vector();
        explicit Vector( T init );
        Vector( T _x, T _y, T _z, T _w );

        T *data();
        const T *data() const;

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
        Vector& operator/=( T s );
    };


    using vec4f = Vector<float,4>;

} // namespace chestnut::engine


#include "vector4.inl"


