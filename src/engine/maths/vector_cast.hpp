#ifndef __CHESTNUT_VECTOR_CAST_H__
#define __CHESTNUT_VECTOR_CAST_H__

#include "vector.hpp"

#include <type_traits>

namespace chestnut
{
    /**
     * @brief Returns vector of given targetN size created from vector v, where targetN is greater than sourceN
     * 
     * @tparam targetN size of target vector
     * @tparam T type of vector data
     * @tparam sourceN size of source vector
     * 
     * @param v source vector
     * @param initRemainVals value of remaining vector fields (all past sourceN)
     * 
     * @return size-casted vector of type T
     */
    template< size_t targetN, typename T, size_t sourceN, typename = typename std::enable_if< ( targetN > sourceN ) >::type >
    Vector<T,targetN> vecCastSizeGreater( const Vector<T,sourceN>& v, T initRemainVals = 1 );

    /**
     * @brief Returns vector of given targetN size created from vector v, where targetN is smaller than sourceN
     * 
     * @tparam targetN size of target vector
     * @tparam T type of vector data
     * @tparam sourceN size of source vector
     * 
     * @param v source vector
     * 
     * @return size-casted vector of type T
     */
    template< size_t targetN, typename T, size_t sourceN, typename = typename std::enable_if< ( targetN < sourceN ) >::type >
    Vector<T,targetN> vecCastSizeSmaller( const Vector<T,sourceN>& v );

    /**
     * @brief Returns vector of given targetN size created from vector v
     * 
     * @tparam targetN size of target vector
     * @tparam T type of vector data
     * @tparam sourceN size of source vector
     * 
     * @param v source vector
     * @param newVals value of new vector fields, if the cast was made to bigger size
     * 
     * @return size-casted vector of type T 
     */
    template< size_t targetN, typename T, size_t sourceN >
    Vector<T,targetN> vecCastSize( const Vector<T,sourceN>& v, T initNewVals = 1 );

    /**
     * @brief Returns vector with data of type targetT created from vector v
     * 
     * @tparam targetT target vector data type
     * @tparam sourceT source vector data type
     * @tparam n vector size
     * @param v source vector
     * 
     * @return datatype-casted vector of size n
     */
    template< typename targetT, typename sourceT, size_t n >
    Vector<targetT,n> vecCastType( const Vector<sourceT,n>& v );

} // namespace chestnut


#include "vector_cast.tpp"


#endif // __CHESTNUT_VECTOR_CAST_H__