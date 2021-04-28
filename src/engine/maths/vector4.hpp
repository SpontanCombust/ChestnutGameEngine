#ifndef __CHESTNUT_VECTOR4_H__
#define __CHESTNUT_VECTOR4_H__

#include "vector.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector<T,4>
    {
        T data[4];

        T &x, &y, &z, &w;
        
        Vector();
        Vector( const Vector& v );
        Vector( T init );
        Vector( T _x, T _y, T _z, T _w );

        Vector& operator=( const Vector& v );
        T& operator[]( size_t i );
        T operator[]( size_t i ) const;
        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( T s );

        std::string toString() const;

        template< typename U >
        operator Vector<U,4>() const;
    };


    template< typename T >
    using vec4 = Vector<T,4>;

    using vec4f = Vector<float,4>;

} // namespace chestnut


#include "vector4.tpp"


#endif // __CHESTNUT_VECTOR4_H__