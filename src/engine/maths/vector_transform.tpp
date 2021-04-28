#include "matrix3.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"

namespace chestnut
{
    template< typename T, size_t n >
    Vector<T,n> vecLeftMultiplyByMatrix( const Matrix<T,n>& m, const Vector<T,n>& v )
    {
        Vector<T,n> res;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                res.data[i] += m.get(i,j) * v.data[j];
            }
        }

        return res;
    }

    template< typename T, size_t n >
    Vector<T,n> operator*( const Matrix<T,n>& m, const Vector<T,n>& v )
    {
        return vecLeftMultiplyByMatrix<T,n>(m,v);
    }



    template< typename T >
    void vecTranslate( Vector<T,2>& v, T tx, T ty )
    {
        Vector<T,3> v3 = Vector<T,3>( (T)v.x, (T)v.y, (T)1 );
        Matrix<T,3> m = matMakeTranslation<T>( tx, ty );
        v3 = vecLeftMultiplyByMatrix<T,3>( m, v3 );

        v.x = v3.x;
        v.y = v3.y;
    }

    template< typename T >
    void vecScale( Vector<T,2>& v, T sx, T sy )
    {
        Vector<T,3> v3 = Vector<T,3>( (T)v.x, (T)v.y, (T)1 );
        Matrix<T,3> m = matMakeScale<T>( sx, sy );
        v3 = vecLeftMultiplyByMatrix<T,3>( m, v3 );

        v.x = v3.x;
        v.y = v3.y;
    }

    template< typename T >
    void vecRotate( Vector<T,2>& v, double angleRad )
    {
        Vector<T,3> v3 = Vector<T,3>( (T)v.x, (T)v.y, (T)1 );
        Matrix<T,3> m = matMakeRotation<T>( angleRad );
        v3 = vecLeftMultiplyByMatrix<T,3>( m, v3 );

        v.x = v3.x;
        v.y = v3.y;
    }



    template< typename T >
    void vecTranslate( Vector<T,3>& v, T tx, T ty, T tz )
    {
        Vector<T,4> v4 = Vector<T,4>( (T)v.x, (T)v.y,(T)v.z, (T)1 );
        Matrix<T,4> m = matMakeTranslation<T>( tx, ty, tz );
        v4 = vecLeftMultiplyByMatrix<T,4>( m, v4 );

        v.x = v4.x;
        v.y = v4.y;
        v.z = v4.z;
    }

    template< typename T >
    void vecScale( Vector<T,3>& v, T sx, T sy, T sz )
    {
        Vector<T,4> v4 = Vector<T,4>( (T)v.x, (T)v.y,(T)v.z, (T)1 );
        Matrix<T,4> m = matMakeScale<T>( sx, sy, sz );
        v4 = vecLeftMultiplyByMatrix<T,4>( m, v4 );

        v.x = v4.x;
        v.y = v4.y;
        v.z = v4.z;
    }

    template< typename T >
    void vecRotate( Vector<T,3>& v, const Vector<T,3>& axis, double angleRad )
    {
        Vector<T,4> v4 = Vector<T,4>( (T)v.x, (T)v.y,(T)v.z, (T)1 );
        Matrix<T,4> m = matMakeRotation<T>( axis, angleRad );
        v4 = vecLeftMultiplyByMatrix<T,4>( m, v4 );

        v.x = v4.x;
        v.y = v4.y;
        v.z = v4.z;
    }



    template< typename T >
    void vecTranslate( Vector<T,4>& v, T tx, T ty, T tz )
    {
        Matrix<T,4> m = matMakeTranslation<T>( tx, ty, tz );
        v = vecLeftMultiplyByMatrix<T,4>( m, v );
    }

    template< typename T >
    void vecScale( Vector<T,4>& v, T sx, T sy, T sz )
    {
        Matrix<T,4> m = matMakeScale<T>( sx, sy, sz );
        v = vecLeftMultiplyByMatrix<T,4>( m, v );
    }

    template< typename T >
    void vecRotate( Vector<T,4>& v, const Vector<T,3>& axis, double angleRad )
    {
        Matrix<T,4> m = matMakeRotation<T>( axis, angleRad );
        v = vecLeftMultiplyByMatrix<T,4>( m, v );
    }

} // namespace chestnut
