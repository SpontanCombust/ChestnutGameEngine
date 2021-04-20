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


    template< typename T >
    using mat4 = Matrix4<T>;
    
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
    Matrix4<T> mat4ScalarProduct( const Matrix4<T>& m, T s );

    template< typename T >
    Matrix4<T> operator*( const Matrix4<T>& m, T s );

    template< typename T >
    Matrix4<T> operator*( T s, const Matrix4<T>& m );


    template< typename T >
    Matrix4<T> mat4MakeOrthographic( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix4<T> mat4MakeFrustum( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix4<T> mat4MakePerspective( T fovy, T aspect, T near, T far );


    template< typename T >
    Matrix4<T> mat4MakeTranslation( T tx, T ty, T tz );


    template< typename T >
    Matrix4<T> mat4MakeScale( T sx, T sy, T sz );


    template< typename T >
    Matrix4<T> mat4MakeRotationX( double angleRad );

    template< typename T >
    Matrix4<T> mat4MakeRotationY( double angleRad );

    template< typename T >
    Matrix4<T> mat4MakeRotationZ( double angleRad );

    template< typename T >
    Matrix4<T> mat4MakeRotation( Vector3<T> axis, double angleRad );

} // namespace chestnut


#include "matrix4.tpp"


#endif // __CHESTNUT_MATRIX4_H__