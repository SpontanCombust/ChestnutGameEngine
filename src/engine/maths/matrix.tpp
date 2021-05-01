#include "engine/misc/exception.hpp"

#include <cstring>
#include <sstream>

namespace chestnut
{    
    template<typename T, size_t n>
    Matrix<T, n>::Matrix()
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if( i == j )
                {
                    data[ j * n + i ] = 1;
                }
                else
                {
                    data[ j * n + i ] = 0;
                }
            }
        }        
    }

    template<typename T, size_t n>
    Matrix<T, n>::Matrix( const Matrix& m ) 
    {
        std::memcpy( data, m.data, sizeof( data ) );
    }

    template<typename T, size_t n>
    Matrix<T, n>::Matrix( T init )
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if( i == j )
                {
                    data[ j * n + i ] = init;
                }
                else
                {
                    data[ j * n + i ] = 0;
                }
            }
        }
    }

    template<typename T, size_t n>
    Matrix<T,n>& Matrix<T, n>::operator=( const Matrix<T,n>& m ) 
    {
        std::memcpy( data, m.data, sizeof( data ) );
        return *this;
    }

    template<typename T, size_t n>
    T Matrix<T, n>::get( size_t row, size_t column ) const
    {
        if( row >= n || column >= n )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        return data[ column * n + row ];
    }

    template<typename T, size_t n>
    void Matrix<T, n>::set( size_t row, size_t column, T val ) 
    {
        if( row >= n || column >= n )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        data[ column * n + row ] = val;
    }

    template<typename T, size_t n>
    T& Matrix<T, n>::operator()( size_t row, size_t column ) 
    {
        if( row >= n || column >= n )
        {
            throw ChestnutException( "Matrix index out of bounds!" );
        }

        return data[ column * n + row ];
    }

    template<typename T, size_t n>
    std::string Matrix<T, n>::toString() const
    {
        std::stringstream ss;

        for (size_t i = 0; i < n; i++)
        {
            ss << "[ ";
            ss << get(i,0);
            for (size_t j = 1; j < n; j++)
            {
                ss << ",\t" << get(i,j);
            }
            ss << " ]\n";
        }
        
        return ss.str();
    }

    

    template< typename T, size_t n >
    Matrix<T,n> matIdentity()
    {
        // default matrix already is identity, function is merely for explicitly stating you want identity matrix
        return Matrix<T,n>();
    }



    template< typename T, size_t n >
    Matrix<T,n> matTransposed( const Matrix<T,n>& m )
    {
        Matrix<T,n> tm;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                tm( i, j ) = m.get( j, i );
            }
        }
        
        return tm;
    }



    template< typename T, size_t n >
    Matrix<T,n> matNegated( const Matrix<T,n>& m )
    {
        Matrix<T,n> nm;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                nm( i, j ) = -m.get( i, j );
            }
        }
        
        return nm;
    }

    template< typename T, size_t n >
    Matrix<T,n> operator-( const Matrix<T,n>& m )
    {
        return matNegated<T,n>(m);
    }



    template< typename T, size_t n >
    Matrix<T,n> matSum( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        Matrix<T,n> sm;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                sm( i, j ) = m1.get( i, j ) + m2.get( i, j );
            }
        }

        return sm;        
    }

    template< typename T, size_t n >
    Matrix<T,n> operator+( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        return matSum<T,n>(m1,m2);
    }



    template< typename T, size_t n >
    Matrix<T,n> matDifference( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        Matrix<T,n> dm;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                dm( i, j ) = m1.get( i, j ) - m2.get( i, j );
            }
        }

        return dm;
    }

    template< typename T, size_t n >
    Matrix<T,n> operator-( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        return matDifference(m1,m2);
    }



    template< typename T, size_t n >
    Matrix<T,n> matProduct( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        Matrix<T,n> pm(0);

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                for (size_t k = 0; k < n; k++)
                {
                    pm( i, j ) += m1.get( i, k ) * m2.get( k, j );
                }
            }
        }
        
        return pm;
    }

    template< typename T, size_t n >
    Matrix<T,n> operator*( const Matrix<T,n>& m1, const Matrix<T,n>& m2 )
    {
        return matProduct<T,n>(m1,m2);
    }

    

    template< typename T, size_t n >
    Matrix<T,n> matScalarProduct( const Matrix<T,n>& m, T s )
    {
        Matrix<T,n> sm;

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                sm( i, j ) = m.get( i, j ) * s;
            }
        }

        return sm;        
    }

    template< typename T, size_t n >
    Matrix<T,n> operator*( const Matrix<T,n>& m, T s )
    {
        return matScalarProduct(m,s);
    }

    template< typename T, size_t n >
    Matrix<T,n> operator*( T s, const Matrix<T,n>& m )
    {
        return matScalarProduct(m,s);
    }

} // namespace chestnut
