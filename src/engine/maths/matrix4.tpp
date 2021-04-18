#include "engine/misc/exception.hpp"

#include <cmath>
#include <sstream>

namespace chestnut
{    
    template< typename T >
    Matrix4<T>::Matrix4() 
    {
        set( 0, 0, 1.0 ); set( 0, 1, 0.0 ); set( 0, 2, 0.0 ); set( 0, 3, 0.0 );
        set( 1, 0, 0.0 ); set( 1, 1, 1.0 ); set( 1, 2, 0.0 ); set( 1, 3, 0.0 );
        set( 2, 0, 0.0 ); set( 2, 1, 0.0 ); set( 2, 2, 1.0 ); set( 2, 3, 0.0 );
        set( 3, 0, 0.0 ); set( 3, 1, 0.0 ); set( 3, 2, 0.0 ); set( 3, 3, 1.0 );
    }

    template< typename T >
    T Matrix4<T>::get( int row, int collumn ) const
    {
        if( row < 0 || row >= 4 || collumn < 0 || collumn >= 4 )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        return data[ collumn * 4 + row ];
    }

    template< typename T >
    void Matrix4<T>::set( int row, int collumn, T val ) 
    {
        if( row < 0 || row >= 4 || collumn < 0 || collumn >= 4 )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        data[ collumn * 4 + row ] = val;
    }

    template< typename T >
    T& Matrix4<T>::operator()( int row, int collumn ) 
    {
        if( row < 0 || row >= 4 || collumn < 0 || collumn >= 4 )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        return data[ collumn * 4 + row ];
    }

    template< typename T >
    std::string Matrix4<T>::toString() const
    {
        std::stringstream ss;

        ss << "[ " << get(0,0) << ",\t" << get(0,1) << ",\t" << get(0,2) << ",\t" << get(0,3) << " ]\n";
        ss << "[ " << get(1,0) << ",\t" << get(1,1) << ",\t" << get(1,2) << ",\t" << get(1,3) << " ]\n";
        ss << "[ " << get(2,0) << ",\t" << get(2,1) << ",\t" << get(2,2) << ",\t" << get(2,3) << " ]\n";
        ss << "[ " << get(3,0) << ",\t" << get(3,1) << ",\t" << get(3,2) << ",\t" << get(3,3) << " ]\n";

        return ss.str();
    }

    

    template< typename T >
    Matrix4<T> mat4Identity()
    {
        // default matrix already is identity, function is merely for explicitly stating you want identity matrix
        return Matrix4<T>();
    }



    template< typename T >
    Matrix4<T> mat4Transposed( const Matrix4<T>& m )
    {
        Matrix4<T> tm;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tm( i, j ) = m.get( j, i );
            }
        }
        
        return tm;
    }



    template< typename T >
    Matrix4<T> mat4Negated( const Matrix4<T>& m )
    {
        Matrix4<T> nm;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                nm( i, j ) = -m.get( i, j );
            }
        }
        
        return nm;
    }

    template< typename T >
    Matrix4<T> operator-( const Matrix4<T>& m )
    {
        return mat4Negated(m);
    }



    template< typename T >
    Matrix4<T> mat4Sum( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        Matrix4<T> sm;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                sm( i, j ) = m1.get( i, j ) + m2.get( i, j );
            }
        }
        
        return sm;
    }

    template< typename T >
    Matrix4<T> operator+( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        return mat4Sum( m1, m2 );
    }



    template< typename T >
    Matrix4<T> mat4Difference( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        Matrix4<T> dm;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                dm( i, j ) = m1.get( i, j ) - m2.get( i, j );
            }
        }
        
        return dm;
    }

    template< typename T >
    Matrix4<T> operator-( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        return mat4Difference( m1, m2 );
    }



    template< typename T >
    Matrix4<T> mat4Product( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        Matrix4<T> pm;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pm( i, j ) = m1.get( i, 0 ) * m2.get( 0, j ) + m1.get( i, 1 ) * m2.get( 1, j ) + m1.get( i, 2 ) * m2.get( 2, j ) + m1.get( i, 3 ) * m2.get( 3, j );         
            }
        }
        
        return pm;
    }

    template< typename T >
    Matrix4<T> operator*( const Matrix4<T>& m1, const Matrix4<T>& m2 )
    {
        return mat4Product( m1, m2 );
    }

    

    template< typename T >
    Matrix4<T> mat4Orthographic( T left, T right, T bottom, T top, T zNear, T zFar )
    {
        Matrix4<T> m;

        m(0,0) = 2.0 / ( right - left );
        m(0,1) = 0.0;
        m(0,2) = 0.0;
        m(0,3) = -( right + left ) / ( right - left );

        m(1,0) = 0.0;
        m(1,1) = 2.0 / ( top - bottom );
        m(1,2) = 0.0;
        m(1,3) = -( top + bottom ) / ( top - bottom );

        m(2,0) = 0.0;
        m(2,1) = 0.0;
        m(2,2) = -2.0 / ( zFar - zNear );
        m(2,3) = -( zFar + zNear ) / ( zFar - zNear );

        m(3,0) = 0.0;
        m(3,1) = 0.0;
        m(3,2) = 0.0;
        m(3,3) = 1.0;

        return m;
    }



    template< typename T >
    Matrix4<T> mat4Translation( T dx, T dy, T dz )
    {
        Matrix4<T> m;

        m(0,3) = dx;
        m(1,3) = dy;
        m(2,3) = dz;

        return m;
    }



    template< typename T >
    Matrix4<T> mat4Scale( T sx, T sy, T sz )
    {
        Matrix4<T> m;

        m(0,0) = sx;
        m(1,1) = sy;
        m(2,2) = sz;

        return m;
    }



    template< typename T >
    Matrix4<T> mat4RotationX( double rxRad )
    {
        Matrix4<T> m;

        double sine = std::sin( rxRad );
        double cosine = std::cos( rxRad );

        m(1,1) = cosine;
        m(1,2) = -sine;
        m(2,2) = sine;
        m(2,3) = cosine;

        return m;
    }

    template< typename T >
    Matrix4<T> mat4RotationY( double ryRad )
    {
        Matrix4<T> m;

        double sine = std::sin( ryRad );
        double cosine = std::cos( ryRad );

        m(0,0) = cosine;
        m(0,2) = sine;
        m(2,0) = -sine;
        m(2,2) = cosine;

        return m;
    }

    template< typename T >
    Matrix4<T> mat4RotationZ( double rzRad )
    {
        Matrix4<T> m;

        double sine = std::sin( rzRad );
        double cosine = std::cos( rzRad );

        m(0,0) = cosine;
        m(0,1) = -sine;
        m(1,0) = sine;
        m(1,1) = cosine;

        return m;
    }

} // namespace chestnut
