#include "chestnut/engine/maths/matrix3.hpp"

namespace chestnut::engine
{
    template
    struct Matrix<float,3>;



    template
    Matrix<float,3> matIdentity();

    template
    Matrix<float,3> matTransposed( const Matrix<float,3>& m );

    template
    Matrix<float,3> matNegated( const Matrix<float,3>& m );

    template
    Matrix<float,3> matSum( const Matrix<float,3>& m1, const Matrix<float,3>& m2 );

    template
    Matrix<float,3> matDifference( const Matrix<float,3>& m1, const Matrix<float,3>& m2 );

    template
    Matrix<float,3> matProduct( const Matrix<float,3>& m1, const Matrix<float,3>& m2 );
    
    template
    Matrix<float,3> matScalarProduct( const Matrix<float,3>& m, float s );

    template
    std::string matToString( const Matrix<float,3>& m );



    template
    Matrix<float,3> matMakeTranslation( float tx, float ty );

    template
    Matrix<float,3> matMakeScale( float sx, float sy );

    template
    Matrix<float,3> matMakeRotation( float angleRad );
    
} // namespace chestnut::engine
