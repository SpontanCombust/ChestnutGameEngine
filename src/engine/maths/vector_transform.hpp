#ifndef __CHESTNUT_VECTOR_TRANSFORM_H__
#define __CHESTNUT_VECTOR_TRANSFORM_H__

#include "vector.hpp"
#include "matrix.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

namespace chestnut
{
    template< typename T, size_t n >
    Vector<T,n> vecLeftMultiplyByMatrix( const Matrix<T,n>& m, const Vector<T,n>& v );

    template< typename T, size_t n >
    Vector<T,n> operator*( const Matrix<T,n>& m, const Vector<T,n>& v );


    template< typename T >
    void vecTranslate( Vector<T,2>& v, T tx, T ty );

    template< typename T >
    void vecScale( Vector<T,2>& v, T sx, T sy );

    template< typename T >
    void vecRotate( Vector<T,2>& v, double angleRad );


    template< typename T >
    void vecTranslate( Vector<T,3>& v, T tx, T ty, T tz );

    template< typename T >
    void vecScale( Vector<T,3>& v, T sx, T sy, T sz );

    template< typename T >
    void vecRotate( Vector<T,3>& v, const Vector<T,3>& axis, double angleRad );


    template< typename T >
    void vecTranslate( Vector<T,4>& v, T tx, T ty, T tz );

    template< typename T >
    void vecScale( Vector<T,4>& v, T sx, T sy, T sz );

    template< typename T >
    void vecRotate( Vector<T,4>& v, const Vector<T,3>& axis, double angleRad );

} // namespace chestnut


#include "vector_transform.tpp"


#endif // __CHESTNUT_VECTOR_TRANSFORM_H__