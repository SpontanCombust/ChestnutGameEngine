#ifndef __CHESTNUT_MATRIX4_H__
#define __CHESTNUT_MATRIX4_H__

#include <string>

namespace chestnut
{
    /*
        A 4x4 matrix

        Data is arranged the same way as OpenGL does matrices:
        00 04 08 12
        01 05 09 13
        02 06 10 14
        03 07 11 15

        Method accessors however allow to intuitively access this data by "collumn" and "row".
    */
    template< typename T >
    struct Matrix4
    {
        T data[16];

        Matrix4();

        T get( int row, int collumn ) const;
        void set( int row, int collumn, T val );

        T& operator()( int row, int collumn );    

        std::string toString() const;
    };


    typedef Matrix4<float> mat4f;


    template< typename T >
    Matrix4<T> mat4Identity();


    template< typename T >
    Matrix4<T> mat4Transposed( const Matrix4<T>& m );


    template< typename T >
    Matrix4<T> mat4Negated( const Matrix4<T>& m );

    template< typename T >
    Matrix4<T> operator-( const Matrix4<T>& m );


    template< typename T >
    Matrix4<T> mat4Sum( const Matrix4<T>& m1, const Matrix4<T>& m2 );

    template< typename T >
    Matrix4<T> operator+( const Matrix4<T>& m1, const Matrix4<T>& m2 );


    template< typename T >
    Matrix4<T> mat4Difference( const Matrix4<T>& m1, const Matrix4<T>& m2 );

    template< typename T >
    Matrix4<T> operator-( const Matrix4<T>& m1, const Matrix4<T>& m2 );


    template< typename T >
    Matrix4<T> mat4Product( const Matrix4<T>& m1, const Matrix4<T>& m2 );

    template< typename T >
    Matrix4<T> operator*( const Matrix4<T>& m1, const Matrix4<T>& m2 );

    
    template< typename T >
    Matrix4<T> mat4Orthographic( T left, T right, T bottom, T top, T zNear, T zFar );


    template< typename T >
    Matrix4<T> mat4Translation( T dx, T dy, T dz );


    template< typename T >
    Matrix4<T> mat4Scale( T sx, T sy, T sz );


    template< typename T >
    Matrix4<T> mat4RotationX( double rxRad );

    template< typename T >
    Matrix4<T> mat4RotationY( double ryRad );

    template< typename T >
    Matrix4<T> mat4RotationZ( double rzRad );

} // namespace chestnut


#include "matrix4.tpp"


#endif // __CHESTNUT_MATRIX4_H__