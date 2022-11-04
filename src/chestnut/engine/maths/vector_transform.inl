#include "chestnut/engine/maths/matrix3.hpp"
#include "chestnut/engine/maths/vector4.hpp"
#include "chestnut/engine/maths/matrix4.hpp"
#include "chestnut/engine/maths/vector_cast.hpp"

namespace chestnut::engine
{
    template< typename T, size_t mn, size_t vn, typename >
    Vector<T,vn> vecLeftMultiplyByMatrix( const Matrix<T,mn>& m, const Vector<T,vn>& v )
    {
        Vector<T,mn> res;
        T *datRes = res.data();

        if constexpr( mn == vn )
        {
            const T *dat = v.data();

            for (size_t i = 0; i < mn; i++)
            {
                for (size_t j = 0; j < mn; j++)
                {
                    datRes[i] += m(i,j) * dat[j];
                }
            }

            return res;
        }
        else
        {
            Vector<T,mn> cast = vecCastSize<mn>(v);
            T *datCast = cast.data();

            for (size_t i = 0; i < mn; i++)
            {
                for (size_t j = 0; j < mn; j++)
                {
                    datRes[i] += m(i,j) * datCast[j];
                }
            }

            return vecCastSize<vn>(res);
        }
    }

    template< typename T, size_t mn, size_t vn, typename >
    Vector<T,vn> operator*( const Matrix<T,mn>& m, const Vector<T,vn>& v )
    {
        return vecLeftMultiplyByMatrix<T,mn,vn>(m,v);
    }



    template< typename T >
    void vecTranslate( Vector<T,2>& v, T tx, T ty )
    {
        Matrix<T,3> m = matMakeTranslation<T>( tx, ty );
        v = m * v;
    }

    template< typename T >
    void vecScale( Vector<T,2>& v, T sx, T sy )
    {
        Matrix<T,3> m = matMakeScale<T>( sx, sy );
        v = m * v;
    }

    template< typename T >
    void vecRotate( Vector<T,2>& v, float angleRad )
    {
        Matrix<T,3> m = matMakeRotation<T>( angleRad );
        v = m * v;
    }



    template< typename T >
    void vecTranslate( Vector<T,3>& v, T tx, T ty, T tz )
    {
        Matrix<T,4> m = matMakeTranslation<T>( tx, ty, tz );
        v = m * v;
    }

    template< typename T >
    void vecScale( Vector<T,3>& v, T sx, T sy, T sz )
    {
        Matrix<T,4> m = matMakeScale<T>( sx, sy, sz );
        v = m * v;
    }

    template< typename T >
    void vecRotate( Vector<T,3>& v, const Vector<T,3>& axis, float angleRad )
    {
        Matrix<T,4> m = matMakeRotation<T>( axis, angleRad );
        v = m * v;
    }



    template< typename T >
    void vecTranslate( Vector<T,4>& v, T tx, T ty, T tz )
    {
        Matrix<T,4> m = matMakeTranslation<T>( tx, ty, tz );
        v = m * v;
    }

    template< typename T >
    void vecScale( Vector<T,4>& v, T sx, T sy, T sz )
    {
        Matrix<T,4> m = matMakeScale<T>( sx, sy, sz );
        v = m * v;
    }

    template< typename T >
    void vecRotate( Vector<T,4>& v, const Vector<T,3>& axis, float angleRad )
    {
        Matrix<T,4> m = matMakeRotation<T>( axis, angleRad );
        v = m * v;
    }

} // namespace chestnut::engine
