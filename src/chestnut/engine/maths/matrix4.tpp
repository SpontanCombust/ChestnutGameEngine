namespace chestnut
{    
    template< typename T >
    Matrix<T,4> matMakeOrthographic( T left, T right, T bottom, T top, T near, T far )
    {
        Matrix<T,4> m;

        m(0,0) = 2.0 / ( right - left );
        m(0,3) = -( right + left ) / ( right - left );

        m(1,1) = 2.0 / ( top - bottom );
        m(1,3) = -( top + bottom ) / ( top - bottom );

        m(2,2) = -2.0 / ( far - near );
        m(2,3) = -( far + near ) / ( far - near );

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakeFrustum( T left, T right, T bottom, T top, T near, T far )
    {
        Matrix<T,4> m(0);

        m(0,0) = 2.0 * near / ( right - left );
        m(0,2) = ( right + left ) / ( right - left );

        m(1,1) = 2.0 * near / ( top - bottom );
        m(1,2) = ( top + bottom ) / ( top - bottom );
        
        m(2,2) = -( far + near ) / ( far - near );
        m(2,3) = -2.0 * far * near / ( far - near );

        m(3,2) = -1.0;

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakePerspective( T fovy, T aspect, T near, T far )
    {
        Matrix<T,4> m(0);

        float cotangent = std::cos( fovy * 0.5 ) / std::sin( fovy * 0.5 );

        m(0,0) = cotangent / aspect;
        m(1,1) = cotangent;
        m(2,2) = ( far + near ) / ( near - far );
        m(2,3) = ( 2 * far * near ) / ( near - far );
        m(3,2) = -1.0;

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakeLookAt( const Vector<T,3>& camera, const Vector<T,3>& target, const Vector<T,3>& up )
    {
        Vector<T,3> cameraDirection = vecNormalized( camera - target );
        Vector<T,3> cameraRight = vecNormalized( vecCrossProduct( up, cameraDirection ) );
        Vector<T,3> cameraUp = vecCrossProduct( cameraDirection, cameraRight );

        Matrix<T,4> m;

        m(0,0) = cameraRight.x;     m(0,1) = cameraRight.y;     m(0,2) = cameraRight.z;
        m(1,0) = cameraUp.x;        m(1,1) = cameraUp.y;        m(1,2) = cameraUp.z;
        m(2,0) = cameraDirection.x; m(2,1) = cameraDirection.y; m(2,2) = cameraDirection.z;

        Matrix<T,4> t = matMakeTranslation( -camera.x, -camera.y, -camera.z );

        return m * t;
    }



    template< typename T >
    Matrix<T,4> matMakeTranslation( T tx, T ty, T tz )
    {
        Matrix<T,4> m;

        m(0,3) = tx;
        m(1,3) = ty;
        m(2,3) = tz;

        return m;
    }



    template< typename T >
    Matrix<T,4> matMakeScale( T sx, T sy, T sz )
    {
        Matrix<T,4> m;

        m(0,0) = sx;
        m(1,1) = sy;
        m(2,2) = sz;

        return m;
    }



    template< typename T >
    Matrix<T,4> matMakeRotationX( float angleRad )
    {
        Matrix<T,4> m;

        float sine = std::sin( angleRad );
        float cosine = std::cos( angleRad );

        m(1,1) = cosine;
        m(1,2) = -sine;
        m(2,1) = sine;
        m(2,2) = cosine;

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakeRotationY( float angleRad )
    {
        Matrix<T,4> m;

        float sine = std::sin( angleRad );
        float cosine = std::cos( angleRad );

        m(0,0) = cosine;
        m(0,2) = sine;
        m(2,0) = -sine;
        m(2,2) = cosine;

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakeRotationZ( float angleRad )
    {
        Matrix<T,4> m;

        float sine = std::sin( angleRad );
        float cosine = std::cos( angleRad );

        m(0,0) = cosine;
        m(0,1) = -sine;
        m(1,0) = sine;
        m(1,1) = cosine;

        return m;
    }

    template< typename T >
    Matrix<T,4> matMakeRotation( Vector<T,3> axis, float angleRad )
    {
        Matrix<T,4> rm;
        float sine, cosine;

        sine = std::sin( angleRad );
        cosine = std::cos( angleRad );
        axis = vecNormalized<T>( axis );

        rm(0,0) = cosine + ( axis.x * axis.x ) * ( 1 - cosine );
        rm(0,1) = axis.x * axis.y * ( 1 - cosine ) - axis.z * sine;
        rm(0,2) = axis.x * axis.z * ( 1 - cosine ) + axis.y * sine;

        rm(1,0) = axis.y * axis.x * ( 1 - cosine ) + axis.z * sine;
        rm(1,1) = cosine + ( axis.y * axis.y ) * ( 1 - cosine );
        rm(1,2) = axis.y * axis.z * ( 1 - cosine ) - axis.x * sine;

        rm(2,0) = axis.z * axis.x * ( 1 - cosine ) - axis.y * sine;
        rm(2,1) = axis.z * axis.y * ( 1 - cosine ) + axis.x * sine;
        rm(2,2) = cosine + ( axis.z * axis.z ) * ( 1 - cosine );

        return rm;
    }

} // namespace chestnut
