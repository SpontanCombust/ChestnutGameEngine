#ifndef __CHESTNUT_ENGINE_VECTOR_H__
#define __CHESTNUT_ENGINE_VECTOR_H__

#include <string>

namespace chestnut::engine
{
    // A mathematical vector with data of type T and size n
    template< typename T, size_t n >
    struct Vector
    {
        T elements[n];

        Vector();
        Vector( T init );

        const T* data() const;
        T* data();

        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( const Vector& v );
        Vector& operator/=( const Vector& v );
        Vector& operator*=( T s );
    };


    template< typename T, size_t n >
    T vecMagnitude( const Vector<T,n>& v );


    template< typename T, size_t n >
    Vector<T,n> vecNormalized( const Vector<T,n>& v );


    template< typename T, size_t n >
    Vector<T,n> vecNegated( const Vector<T,n>& v );

    template< typename T, size_t n >
    Vector<T,n> operator-( const Vector<T,n>& v );


    template< typename T, size_t n >
    Vector<T,n> vecSum( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    Vector<T,n> operator+( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    Vector<T,n> vecDifference( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template<typename T, size_t n>
    Vector<T,n> operator-( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    Vector<T,n> vecScalarProduct( const Vector<T,n>& v, T s );

    template< typename T, size_t n >
    Vector<T,n> operator*( T s, const Vector<T,n>& v );

    template< typename T, size_t n >
    Vector<T,n> operator*( const Vector<T,n>& v, T s );


    template< typename T, size_t n >
    T vecDotProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    Vector<T,n> vecComponentProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    Vector<T,n> operator*( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    Vector<T,n> vecComponentQuotient( const Vector<T,n>& v1, const Vector<T,n>& v2 );

    template< typename T, size_t n >
    Vector<T,n> operator/( const Vector<T,n>& v1, const Vector<T,n>& v2 );


    template< typename T, size_t n >
    std::string vecToString( const Vector<T,n>& v );

} // namespace chestnut::engine


#include "vector.tpp"


#endif // __CHESTNUT_ENGINE_VECTOR_H__