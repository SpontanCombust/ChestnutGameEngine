#include <cmath>

namespace chestnut
{
    template< typename T >
    Matrix<T,3> matMakeTranslation( T tx, T ty )
    {
        Matrix<T,3> m;

        m(0,2) = tx;
        m(1,2) = ty;

        return m;
    }

    template< typename T >
    Matrix<T,3> matMakeScale( T sx, T sy )
    {
        Matrix<T,3> m;

        m(0,0) = sx;
        m(1,1) = sy;

        return m;
    }

    template< typename T >
    Matrix<T,3> matMakeRotation( float angleRad )
    {
        Matrix<T,3> m;

        float sine = std::sin( angleRad );
        float cosine = std::cos( angleRad );

        m(0,0) = cosine;
        m(0,1) = -sine;
        m(1,0) = sine;
        m(1,1) = cosine;

        return m;
    }

} // namespace chestnut
