#pragma once


#include "chestnut/engine/maths/matrix.hpp"
#include "chestnut/engine/maths/vector3.hpp"

#include <string>

namespace chestnut::engine
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

} // namespace chestnut::engine


#include "matrix4.inl"


