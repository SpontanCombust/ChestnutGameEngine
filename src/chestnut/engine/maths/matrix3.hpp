#pragma once


#include "matrix.hpp"

#include <string>

namespace chestnut::engine
{
    using mat3f = Matrix<float,3>;


    template< typename T >
    Matrix<T,3> matMakeTranslation( T tx, T ty );

    template< typename T >
    Matrix<T,3> matMakeScale( T sx, T sy );

    template< typename T >
    Matrix<T,3> matMakeRotation( float angleRad );

} // namespace chestnut::engine


#include "matrix3.tpp"


