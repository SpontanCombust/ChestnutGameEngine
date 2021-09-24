#ifndef __CHESTNUT_ENGINE_MATRIX4_H__
#define __CHESTNUT_ENGINE_MATRIX4_H__

#include "matrix.hpp"
#include "vector3.hpp"

#include <string>

namespace chestnut
{
    using mat4f = Matrix<float,4>;


    template< typename T >
    Matrix<T,4> matMakeOrthographic( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix<T,4> matMakeFrustum( T left, T right, T bottom, T top, T near, T far );

    template< typename T >
    Matrix<T,4> matMakePerspective( T fovy, T aspect, T near, T far );

    template< typename T >
    Matrix<T,4> matMakeLookAt( const Vector<T,3>& camera, const Vector<T,3>& target, const Vector<T,3>& up = { 0.0, 1.0, 0.0 } );


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


#endif // __CHESTNUT_ENGINE_MATRIX4_H__