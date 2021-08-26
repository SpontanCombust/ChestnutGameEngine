#include "matrix4.hpp"

namespace chestnut
{
    template<>
    struct Matrix<float,4>;



    template<>
    Matrix<float,4> matIdentity();


    template<>
    Matrix<float,4> matTransposed( const Matrix<float,4>& m );


    template<>
    Matrix<float,4> matNegated( const Matrix<float,4>& m );

    template<>
    Matrix<float,4> operator-( const Matrix<float,4>& m );


    template<>
    Matrix<float,4> matSum( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );

    template<>
    Matrix<float,4> operator+( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );


    template<>
    Matrix<float,4> matDifference( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );

    template<>
    Matrix<float,4> operator-( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );


    template<>
    Matrix<float,4> matProduct( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );

    template<>
    Matrix<float,4> operator*( const Matrix<float,4>& m1, const Matrix<float,4>& m2 );

    
    template<>
    Matrix<float,4> matScalarProduct( const Matrix<float,4>& m, float s );

    template<>
    Matrix<float,4> operator*( const Matrix<float,4>& m, float s );

    template<>
    Matrix<float,4> operator*( float s, const Matrix<float,4>& m );


    template<>
    std::string matToString( const Matrix<float,4>& m );



    template<>
    Matrix<float,4> matMakeOrthographic( float left, float right, float bottom, float top, float near, float far );

    template<>
    Matrix<float,4> matMakeFrustum( float left, float right, float bottom, float top, float near, float far );

    template<>
    Matrix<float,4> matMakePerspective( float fovy, float aspect, float near, float far );


    template<>
    Matrix<float,4> matMakeTranslation( float tx, float ty, float tz );


    template<>
    Matrix<float,4> matMakeScale( float sx, float sy, float sz );


    template<>
    Matrix<float,4> matMakeRotationX( float angleRad );

    template<>
    Matrix<float,4> matMakeRotationY( float angleRad );

    template<>
    Matrix<float,4> matMakeRotationZ( float angleRad );

    template<>
    Matrix<float,4> matMakeRotation( Vector<float,3> axis, float angleRad );

} // namespace chestnut
