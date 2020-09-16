#include "core/vector.hpp"

#include <cmath>

namespace vector
{
    template< typename T >
    T Vector2<T>::getMagnitude() const
    {
        return sqrt( x * x + y * y );
    }



    template< typename T >
    void Vector2<T>::normalize() 
    {
        if( x != 0 && y != 0 )
        {
            T mag = getMagnitude();
            x /= mag;
            y /= mag;
        }
    }

    template< typename T >
    Vector2<T> getNormalized( const Vector2<T>& v ) 
    {
        Vector2<T> vCopy = v;
        vCopy.normalize();
        return vCopy;
    }



    template< typename T >
    void Vector2<T>::negate() 
    {
        x = -x;
        y = -y;
    }

    template< typename T >
    Vector2<T> getNegated( const Vector2<T>& v ) 
    {
        Vector2<T> vCopy = v;
        vCopy.negate();
        return vCopy;
    }

    template< typename T >
    Vector2<T> operator-( const Vector2<T>& v ) 
    {
        Vector2<T> vCopy = v;
        vCopy.negate();
        return vCopy;
    }



    template< typename T >
    void Vector2<T>::add( const Vector2<T>& other ) 
    {
        x += other.x;
        y += other.y;
    }

    template< typename T >
    void Vector2<T>::operator+=( const Vector2<T>& other ) 
    {
        add(other);
    }

    template< typename T >
    Vector2<T> getSum( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        Vector2<T> v1Copy = v1;
        v1Copy.add(v2);
        return v1Copy;
    }

    template< typename T >
    Vector2<T> operator+( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        Vector2<T> v1Copy = v1;
        v1Copy.add(v2);
        return v1Copy;
    }



    template< typename T >
    void Vector2<T>::subtract( const Vector2<T>& other ) 
    {
        x -= other.x;
        y -= other.y;
    }

    template< typename T >
    void Vector2<T>::operator-=( const Vector2<T>& other ) 
    {
        subtract(other);
    }

    template< typename T >
    Vector2<T> getDifference( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        Vector2<T> v1Copy = v1;
        v1Copy.subtract(v2);
        return v1Copy;
    }

    template<typename T>
    Vector2<T> operator-( const Vector2<T>& v1, const Vector2<T>& v2 )
    {
        Vector2<T> v1Copy = v1;
        v1Copy.subtract(v2);
        return v1Copy;
    }



    template< typename T >
    void Vector2<T>::multiplyByScalar( const T s ) 
    {
        x *= s;
        y *= s;
    }

    template< typename T >
    void Vector2<T>::operator*=( const T s ) 
    {
        multiplyByScalar(s);
    }

    template< typename T >
    Vector2<T> getScaled( const Vector2<T>& v, T s ) 
    {
        Vector2<T> vCopy = v;
        vCopy.multiplyByScalar(s);
        return vCopy;
    }

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v ) 
    {
        Vector2<T> vCopy = v;
        vCopy.multiplyByScalar(s);
        return vCopy;
    }

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s ) 
    {
        Vector2<T> vCopy = v;
        vCopy.multiplyByScalar(s);
        return vCopy;
    }



    template< typename T >
    T Vector2<T>::multiplyByVecDot( const Vector2<T>& other ) const
    {
        return x * other.x + y * other.y;
    }

    template< typename T >
    T getDotProduct( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        return v1.multiplyByVecDot(v2);
    }



    template<typename T>
    std::string Vector2<T>::to_string() 
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
    }
}
