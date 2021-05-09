#ifndef __CHESTNUT_VECTOR3_H__
#define __CHESTNUT_VECTOR3_H__

#include "vector.hpp"
#include "vector2.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector<T,3>
    {
        T data[3];

        T& x(); 
        const T& x() const;
        T& y(); 
        const T& y() const;
        T& z();
        const T& z() const;

        Vector();
        Vector( const Vector& v );
        Vector( T init );
        Vector( T _x, T _y, T _z );

        Vector& operator=( const Vector& v );
        T& operator[]( size_t i );
        T operator[]( size_t i ) const;
        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( T s );

        std::string toString() const;
    };


    template< typename T >
    using vec3 = Vector<T,3>;

    // predefined vectors //
    using vec3f = Vector<float,3>;
    using vec3i = Vector<int,3>;


    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,2>& v1, const Vector<T,2>& v2 );

    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,3>& v1, const Vector<T,3>& v2 );

} // namespace chestnut


#include "vector3.tpp"


#endif // __CHESTNUT_VECTOR3_H__
