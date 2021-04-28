#include "engine/misc/exception.hpp"

#include <cmath>
#include <cstring>

namespace chestnut
{    
    template<typename T, size_t n>
    Vector<T, n>::Vector()
    : data{0}
    {

    }

    template<typename T, size_t n>
    Vector<T, n>::Vector(const Vector<T,n>& v) 
    {
        std::memcpy( data, v.data, sizeof( data ) );
    }

    template<typename T, size_t n>
    Vector<T, n>::Vector( T init ) 
    : data{ init }
    {

    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator=(const Vector<T,n>& v ) 
    {
        std::memcpy( data, v.data, sizeof( data ) );
        return *this;
    }

    template<typename T, size_t n>
    T& Vector<T, n>::operator[]( size_t i ) 
    {
        if( i >= n )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
    }

    template<typename T, size_t n>
    T Vector<T, n>::operator[]( size_t i ) const
    {
        if( i >= n )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator+=( const Vector<T,n>& v ) 
    {
        for (size_t i = 0; i < n; i++)
        {
            data[i] += v.data[i];
        }
        
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator-=( const Vector<T,n>& v ) 
    {
        *this = vecDifference<T,n>( *this, v );
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,n>( *this, s );
        return *this;
    }

    template<typename T, size_t n>
    std::string Vector<T, n>::toString() const
    {
        std::string str;

        str += "[ ";
        str += data[0];
        for (size_t i = 1; i < n; i++)
        {
            str +=  ", " + std::to_string( data[i] );
        }
        str += " ]";
        
        return str;
    }

    template< typename T, size_t n >
    template< typename U >
    Vector<T,n>::operator Vector<U,n>() const
    {
        Vector<U,n> other;

        for (size_t i = 0; i < n; i++)
        {
            other.data[i] = static_cast<U>( this->data[i] );
        }
        
        return other;
    }



    template< typename T, size_t n >
    T vecMagnitude( const Vector<T,n>& v )
    {
        T prod = 0;

        for (size_t i = 0; i < n; i++)
        {
            prod += v.data[i] * v.data[i];
        }
        
        return std::sqrt( prod );
    }



    template< typename T, size_t n >
    Vector<T,n> vecNormalized( const Vector<T,n>& v )
    {
        Vector<T,n> other;
        T mag = vecMagnitude<T,n>(v);

        for (size_t i = 0; i < n; i++)
        {
            other.data[i] = v.data[i] / mag;
        }
        
        return other;
    }



    template< typename T, size_t n >
    Vector<T,n> vecNegated( const Vector<T,n>& v )
    {
        Vector<T,n> other;

        for (size_t i = 0; i < n; i++)
        {
            other.data[i] = -v.data[i];
        }

        return other;
    }

    template< typename T, size_t n >
    Vector<T,n> operator-( const Vector<T,n>& v )
    {
        return vecNegated<T,n>(v);
    }



    template< typename T, size_t n >
    Vector<T,n> vecSum( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> sum;

        for (size_t i = 0; i < n; i++)
        {
            sum.data[i] = v1.data[i] + v2.data[i];
        }

        return sum;
    }

    template< typename T, size_t n >
    Vector<T,n> operator+( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        return vecSum<T,n>(v1,v2);
    }



    template< typename T, size_t n >
    Vector<T,n> vecDifference( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> diff;

        for (size_t i = 0; i < n; i++)
        {
            diff.data[i] = v1.data[i] - v2.data[i];
        }

        return diff;
    }

    template<typename T, size_t n>
    Vector<T,n> operator-( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        return vecDifference<T,n>(v1,v2);
    }



    template< typename T, size_t n >
    Vector<T,n> vecScalarProduct( const Vector<T,n>& v, T s )
    {
        Vector<T,n> scaled;

        for (size_t i = 0; i < n; i++)
        {
            scaled.data[i] = v.data[i] * s;
        }

        return scaled;
    }

    template< typename T, size_t n >
    Vector<T,n> operator*( T s, const Vector<T,n>& v )
    {
        return vecScalarProduct<T,n>(v,s);
    }

    template< typename T, size_t n >
    Vector<T,n> operator*( const Vector<T,n>& v, T s )
    {
        return vecScalarProduct<T,n>(v,s);
    }



    template< typename T, size_t n >
    T vecDotProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        T prod = 0;

        for (size_t i = 0; i < n; i++)
        {
            prod += v1.data[i] * v2.data[i];
        }
        
        return prod;
    }

} // namespace chestnut
