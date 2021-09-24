#ifndef __CHESTNUT_ENGINE_VECTOR_TRANSFORM_H__
#define __CHESTNUT_ENGINE_VECTOR_TRANSFORM_H__

#include "vector.hpp"
#include "matrix.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"

namespace chestnut
{
    /**
     * @brief Perform multiplication matrix * vector, where if vector is smaller size than matrix side, 
     * it can be automatically internally converted to bigger size for the purpose of calculation
     * and then converted back on return 
     * 
     * @tparam T type of vector and matrix
     * @tparam mn size of matrix
     * @tparam vn size of vector
     */
    template< typename T, size_t mn, size_t vn, typename = typename std::enable_if<( mn >= vn )>::type >
    Vector<T,vn> vecLeftMultiplyByMatrix( const Matrix<T,mn>& m, const Vector<T,vn>& v );

    template< typename T, size_t mn, size_t vn, typename = typename std::enable_if<( mn >= vn )>::type >
    Vector<T,vn> operator*( const Matrix<T,mn>& m, const Vector<T,vn>& v );


    template< typename T >
    void vecTranslate( Vector<T,2>& v, T tx, T ty );

    template< typename T >
    void vecScale( Vector<T,2>& v, T sx, T sy );

    template< typename T >
    void vecRotate( Vector<T,2>& v, float angleRad );


    template< typename T >
    void vecTranslate( Vector<T,3>& v, T tx, T ty, T tz );

    template< typename T >
    void vecScale( Vector<T,3>& v, T sx, T sy, T sz );

    template< typename T >
    void vecRotate( Vector<T,3>& v, const Vector<T,3>& axis, float angleRad );


    template< typename T >
    void vecTranslate( Vector<T,4>& v, T tx, T ty, T tz );

    template< typename T >
    void vecScale( Vector<T,4>& v, T sx, T sy, T sz );

    template< typename T >
    void vecRotate( Vector<T,4>& v, const Vector<T,3>& axis, float angleRad );

} // namespace chestnut


#include "vector_transform.tpp"


#endif // __CHESTNUT_ENGINE_VECTOR_TRANSFORM_H__