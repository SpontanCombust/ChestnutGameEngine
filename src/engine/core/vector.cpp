#include "engine/core/vector.hpp"

#include <cmath>

namespace chestnut
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
    Vector2<T> vec2GetNormalized( const Vector2<T>& v ) 
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
    Vector2<T> vec2GetNegated( const Vector2<T>& v ) 
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
    Vector2<T> vec2GetSum( const Vector2<T>& v1, const Vector2<T>& v2 ) 
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
    Vector2<T> vec2GetDifference( const Vector2<T>& v1, const Vector2<T>& v2 ) 
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
    Vector2<T> vec2GetScaled( const Vector2<T>& v, T s ) 
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
    T vec2GetDotProduct( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        return v1.multiplyByVecDot(v2);
    }



    std::string vector2fToString( Vector2f v ) 
    {
        return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
    }

    std::string vector2iToString( Vector2i v ) 
    {
        return "[ " + std::to_string(v.x) + ", " + std::to_string(v.y) + " ]";
    }

} // namespace chestnut
