#ifndef __CHESTNUT_VECTOR2_H__
#define __CHESTNUT_VECTOR2_H__

#include "vector.hpp"

namespace chestnut
{
    template< typename T >
    struct Vector<T,2>
    {
        T x, y;

        Vector();
        Vector( T init );
        Vector( T _x, T _y );

        T *data();
        const T *data() const;

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
    };


    // predefined vectors //
    using vec2f = Vector<float,2>;
    using vec2i = Vector<int,2>;

} // namespace chestnut


#include "vector2.tpp"


#endif // __CHESTNUT_VECTOR2_H__
