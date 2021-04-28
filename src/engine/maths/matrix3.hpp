#ifndef __CHESTNUT_MATRIX3_H__
#define __CHESTNUT_MATRIX3_H__

#include "matrix.hpp"

#include <string>

namespace chestnut
{
    template< typename T >
    using mat3 = Matrix<T,3>;

    using mat3f = Matrix<float,3>;


    template< typename T >
    Matrix<T,3> matMakeTranslation( T tx, T ty );

    template< typename T >
    Matrix<T,3> matMakeScale( T sx, T sy );

    template< typename T >
    Matrix<T,3> matMakeRotation( double angleRad );

} // namespace chestnut


#include "matrix3.tpp"


#endif // __CHESTNUT_MATRIX3_H__