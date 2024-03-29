#include "chestnut/engine/misc/exception.hpp"

#include <algorithm> // fill_n
#include <cmath> // sqrt
#include <sstream>

namespace chestnut::engine
{    
    template<typename T, size_t n>
    Vector<T, n>::Vector()
    {
        std::fill_n( elements, n, 0 );
    }

    template<typename T, size_t n>
    Vector<T, n>::Vector( T init ) 
    {
        std::fill_n( elements, n, init );
    }

    template<typename T, size_t n>
    const T* Vector<T, n>::data() const
    {
        return elements;
    }

    template<typename T, size_t n>
    T* Vector<T, n>::data()
    {
        return elements;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator+=( const Vector<T,n>& v ) 
    {
        *this = vecSum<T,n>( *this, v );
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator-=( const Vector<T,n>& v ) 
    {
        *this = vecDifference<T,n>( *this, v );
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator*=( const Vector<T,n>& v ) 
    {
        *this = vecComponentProduct<T,n>( *this, v );
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator/=( const Vector<T,n>& v ) 
    {
        *this = vecComponentQuotient<T,n>( *this, v );
        return *this;
    }

    template<typename T, size_t n>
    Vector<T,n>& Vector<T, n>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,n>( *this, s );
        return *this;
    }

    template< typename T, size_t n >
    Vector<T,n>& Vector<T, n>::operator/=( T s )
    {
        *this = vecScalarQuotient<T,n>( *this, s );
        return *this;
    }




    template< typename T, size_t n >
    T vecMagnitudeSquared( const Vector<T,n>& v )
    {
        T prod = 0;
        const T *dat = v.data();

        for (size_t i = 0; i < n; i++)
        {
            prod += dat[i] * dat[i];
        }
        
        return prod;
    }

    template< typename T, size_t n >
    T vecMagnitude( const Vector<T,n>& v )
    {
        return (T)std::sqrt(vecMagnitudeSquared<T,n>(v));
    }

    template< typename T, size_t n >
    Vector<T,n> vecNormalized( const Vector<T,n>& v )
    {
        T mag = vecMagnitude<T,n>(v);

        if(mag == (T)0)
        {
            return Vector<T,n>(0);
        }

        Vector<T,n> other;
        const T *dat = v.data();
        T *datOther = other.data();

        for (size_t i = 0; i < n; i++)
        {
            datOther[i] = dat[i] / mag;
        }
        
        return other;
    }

    template< typename T, size_t n >
    Vector<T,n> vecNegated( const Vector<T,n>& v )
    {
        Vector<T,n> other;
        const T *dat = v.data();
        T *datOther = other.data();

        for (size_t i = 0; i < n; i++)
        {
            datOther[i] = -dat[i];
        }

        return other;
    }

    template< typename T, size_t n >
    Vector<T,n> vecSum( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> sum;
        const T *dat1 = v1.data();
        const T *dat2 = v2.data();
        T *datSum = sum.data();

        for (size_t i = 0; i < n; i++)
        {
            datSum[i] = dat1[i] + dat2[i];
        }

        return sum;
    }

    template< typename T, size_t n >
    Vector<T,n> vecDifference( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> diff;
        const T *dat1 = v1.data();
        const T *dat2 = v2.data();
        T *datDiff = diff.data();

        for (size_t i = 0; i < n; i++)
        {
            datDiff[i] = dat1[i] - dat2[i];
        }

        return diff;
    }

    template< typename T, size_t n >
    Vector<T,n> vecScalarProduct( const Vector<T,n>& v, T s )
    {
        Vector<T,n> scaled;
        const T *dat = v.data();
        T *datScaled = scaled.data();

        for (size_t i = 0; i < n; i++)
        {
            datScaled[i] = dat[i] * s;
        }

        return scaled;
    }

    template< typename T, size_t n >
    Vector<T,n> vecScalarQuotient( const Vector<T,n>& v, T s )
    {
        Vector<T,n> scaled;
        const T *dat = v.data();
        T *datScaled = scaled.data();

        for (size_t i = 0; i < n; i++)
        {
            datScaled[i] = dat[i] / s;
        }

        return scaled;   
    }

    template< typename T, size_t n >
    T vecDotProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        T prod = 0;
        const T *dat1 = v1.data();
        const T *dat2 = v2.data();

        for (size_t i = 0; i < n; i++)
        {
            prod += dat1[i] * dat2[i];
        }
        
        return prod;
    }

    template< typename T, size_t n >
    Vector<T,n> vecComponentProduct( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> prod;

        const T *dat1 = v1.data();
        const T *dat2 = v2.data();
        T *datProd = prod.data();

        for (size_t i = 0; i < n; i++)
        {
            datProd[i] = dat1[i] * dat2[i];
        }

        return prod;
    }
    
    template< typename T, size_t n >
    Vector<T,n> vecComponentQuotient( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        Vector<T,n> quot;

        const T *dat1 = v1.data();
        const T *dat2 = v2.data();
        T *datQuot = quot.data();

        for (size_t i = 0; i < n; i++)
        {
            datQuot[i] = dat1[i] / dat2[i];
        }

        return quot;
    }

    template< typename T, size_t n >
    bool vecEquality( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        const T *dat1 = v1.data();
        const T *dat2 = v2.data();

        for (size_t i = 0; i < n; i++)
        {
            if (dat1[i] != dat2[i])
            {
                return false;
            }
        }

        return true;
    }

    template< typename T, size_t n >
    bool vecInequality( const Vector<T,n>& v1, const Vector<T,n>& v2 )
    {
        const T *dat1 = v1.data();
        const T *dat2 = v2.data();

        for (size_t i = 0; i < n; i++)
        {
            if (dat1[i] != dat2[i])
            {
                return true;
            }
        }

        return false;
    }

    template< typename T, size_t n >
    std::string vecToString( const Vector<T,n>& v )
    {
        std::stringstream ss;
        const T *dat = v.data();

        ss << "[ ";
        ss << dat[0];
        for (size_t i = 1; i < n; i++)
        {
            ss <<  ", " << dat[i];
        }
        ss << " ]";
        
        return ss.str();
    }

} // namespace chestnut::engine
