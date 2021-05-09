#ifndef __CHESTNUT_VECTOR2_H__
#define __CHESTNUT_VECTOR2_H__

#include "vector.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector<T,2>
    {
        T data[2];

        T& x(); 
        const T& x() const;
        T& y(); 
        const T& y() const;

        Vector();
        Vector( const Vector& v );
        Vector( T init );
        Vector( T _x, T _y );

        Vector& operator=( const Vector& v );
        T& operator[]( size_t i );
        T operator[]( size_t i ) const;
        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( T s );

        std::string toString() const;
    };


    template< typename T >
    using vec2 = Vector<T,2>;
    
    // predefined vectors //
    using vec2f = Vector<float,2>;
    using vec2i = Vector<int,2>;

} // namespace chestnut


#include "vector2.tpp"


#endif // __CHESTNUT_VECTOR2_H__
