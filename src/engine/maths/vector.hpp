#ifndef __CHESTNUT_VECTOR_H__
#define __CHESTNUT_VECTOR_H__

#include <string>

namespace chestnut
{
    // A mathematical vector with data of type T and size n
    template< typename T, size_t n >
    struct Vector
    {
        T data[n];

        Vector();
        Vector( const Vector& v );
        Vector( T init );

        Vector& operator=( const Vector& v );
        T& operator[]( size_t i );
        T operator[]( size_t i ) const;
        Vector& operator+=( const Vector& v );
        Vector& operator-=( const Vector& v );
        Vector& operator*=( T s );

        std::string toString() const;

        template< typename U >
        operator Vector<U,n>() const;
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
    T operator*( Vector<T,n> v1, Vector<T,n> v2 ) = delete; // forbidden due to ambiguity between dot and cross product

} // namespace chestnut


#include "vector.tpp"


#endif // __CHESTNUT_VECTOR_H__