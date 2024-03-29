#pragma once


#include "chestnut/engine/maths/vector.hpp"

namespace chestnut::engine
{
    template< typename T >
    struct Vector<T,2>
    {
        T x, y;

        Vector();
        explicit Vector( T init );
        Vector( T _x, T _y );

        T *data();
        const T *data() const;

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
        Vector& operator/=( T s );
    };


    // predefined vectors //
    using vec2f = Vector<float,2>;
    using vec2i = Vector<int,2>;

} // namespace chestnut::engine


#include "vector2.inl"


