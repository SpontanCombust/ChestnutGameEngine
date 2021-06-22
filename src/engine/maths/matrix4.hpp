#ifndef __CHESTNUT_MATRIX4_H__
#define __CHESTNUT_MATRIX4_H__

#include "matrix.hpp"
#include "vector3.hpp"

#include <string>

namespace chestnut
{
    template< typename T, size_t n >
    using mat4 = Matrix<T,n>;
    
    using mat4f = Matrix<float,4>;


    template< typename T >
    Matrix<T,4> matMakeOrthographic( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix<T,4> matMakeFrustum( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix<T,4> matMakePerspective( T fovy, T aspect, T near, T far );


    template< typename T >
    Matrix<T,4> matMakeTranslation( T tx, T ty, T tz );


    template< typename T >
    Matrix<T,4> matMakeScale( T sx, T sy, T sz );


    template< typename T >
    Matrix<T,4> matMakeRotationX( float angleRad );

    template< typename T >
    Matrix<T,4> matMakeRotationY( float angleRad );

    template< typename T >
    Matrix<T,4> matMakeRotationZ( float angleRad );

    template< typename T >
    Matrix<T,4> matMakeRotation( Vector<T,3> axis, float angleRad );

} // namespace chestnut


#include "matrix4.tpp"


#endif // __CHESTNUT_MATRIX4_H__