#pragma once


#include <string>

namespace chestnut::engine
{
    /*
        A mathematical square matrix with data of type and number of both rows and columns equal n 

        Data is always arranged in memory the same way as OpenGL does matrices.
        For example for a 4x4 it would be:
        00 04 08 12
        01 05 09 13
        02 06 10 14
        03 07 11 15

        Method accessors however allow to intuitively access this data by "column" and "row" 
        without having to think about whether it's row-major, column-major or whatever.
    */
    template< typename T, size_t n >
    struct Matrix
    {
        T elements[ n * n ];

        Matrix();
        explicit Matrix( T init );

        const T* data() const;
        T *data();

        // Will throw std::out_of_range if eighter row or column are of of range
        T get( size_t row, size_t column ) const;
        // Will throw std::out_of_range if eighter row or column are of of range
        void set( size_t row, size_t column, T val );
        // Will throw std::out_of_range if eighter row or column are of of range
        T& operator()( size_t row, size_t column );
        // Will throw std::out_of_range if eighter row or column are of of range
        T operator()( size_t row, size_t column ) const;
    };


    template< typename T, size_t n >
    Matrix<T,n> matIdentity();


    template< typename T, size_t n >
    Matrix<T,n> matTransposed( const Matrix<T,n>& m );


    template< typename T, size_t n >
    Matrix<T,n> matNegated( const Matrix<T,n>& m );

    template< typename T, size_t n >
    inline Matrix<T,n> operator-( const Matrix<T,n>& m ) { return matNegated( m ); }


    template< typename T, size_t n >
    Matrix<T,n> matSum( const Matrix<T,n>& m1, const Matrix<T,n>& m2 );

    template< typename T, size_t n >
    inline Matrix<T,n> operator+( const Matrix<T,n>& m1, const Matrix<T,n>& m2 ) { return matSum( m1, m2 ); }


    template< typename T, size_t n >
    Matrix<T,n> matDifference( const Matrix<T,n>& m1, const Matrix<T,n>& m2 );

    template< typename T, size_t n >
    inline Matrix<T,n> operator-( const Matrix<T,n>& m1, const Matrix<T,n>& m2 ) { return matDifference( m1, m2 ); }


    template< typename T, size_t n >
    Matrix<T,n> matProduct( const Matrix<T,n>& m1, const Matrix<T,n>& m2 );

    template< typename T, size_t n >
    inline Matrix<T,n> operator*( const Matrix<T,n>& m1, const Matrix<T,n>& m2 ) { return matProduct( m1, m2 ); }

    
    template< typename T, size_t n >
    Matrix<T,n> matScalarProduct( const Matrix<T,n>& m, T s );

    template< typename T, size_t n >
    inline Matrix<T,n> operator*( const Matrix<T,n>& m, T s ) { return matScalarProduct( m, s ); }

    template< typename T, size_t n >
    inline Matrix<T,n> operator*( T s, const Matrix<T,n>& m ) { return matScalarProduct( m, s ); }


    template< typename T, size_t n >
    std::string matToString( const Matrix<T,n>& m );

} // namespace chestnut::engine


#include "matrix.inl"


