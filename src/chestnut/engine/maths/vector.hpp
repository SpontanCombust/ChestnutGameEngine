#pragma once


#include <string>

namespace chestnut::engine
{
    // A mathematical vector with data of type T and size n
    template< typename T, size_t n >
    struct Vector
    {
        T elements[n];

        Vector();
        explicit Vector( T init );

        const T* data() const;
        T* data();

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
        Vector& operator/=( T s );
    };


    template< typename T, size_t n >
    T vecMagnitude( const Vector<T,n>& v );


    template< typename T, size_t n >
    Vector<T,n> vecNormalized( const Vector<T,n>& v );


    template< typename T, size_t n >
    Vector<T,n> vecNegated( const Vector<T,n>& v );

    template< typename T, size_t n >
    inline Vector<T,n> operator-( const Vector<T,n>& v ) { return vecNegated( v ); }


    template< typename T, size_t n >
    Vector<T,n> vecSum( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    inline Vector<T,n> operator+( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecSum( v1, v2 ); }


    template< typename T, size_t n >
    Vector<T,n> vecDifference( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template<typename T, size_t n>
    inline Vector<T,n> operator-( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecDifference( v1, v2 ); }


    template< typename T, size_t n >
    Vector<T,n> vecScalarProduct( const Vector<T,n>& v, T s );

    template< typename T, size_t n >
    inline Vector<T,n> operator*( T s, const Vector<T,n>& v ) { return vecScalarProduct( v, s ); }

    template< typename T, size_t n >
    inline Vector<T,n> operator*( const Vector<T,n>& v, T s ) { return vecScalarProduct( v, s ); }


    template< typename T, size_t n >
    Vector<T,n> vecScalarQuotient( const Vector<T,n>& v, T s );

    template< typename T, size_t n >
    inline Vector<T,n> operator/( const Vector<T,n>& v, T s ) { return vecScalarQuotient( v, s ); }


    template< typename T, size_t n >
    T vecDotProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    Vector<T,n> vecComponentProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    inline Vector<T,n> operator*( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecComponentProduct( v1, v2 ); }


    template< typename T, size_t n >
    Vector<T,n> vecComponentQuotient( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    inline Vector<T,n> operator/( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecComponentQuotient( v1, v2 ); }


    template< typename T, size_t n >
    bool vecEquality( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    inline bool operator==( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecEquality( v1, v2 ); }

    template< typename T, size_t n >
    bool vecInequality( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    inline bool operator!=( const Vector<T,n>& v1, const Vector<T,n>& v2 ) { return vecInequality( v1, v2 ); }


    template< typename T, size_t n >
    std::string vecToString( const Vector<T,n>& v );

} // namespace chestnut::engine


#include "vector.inl"


