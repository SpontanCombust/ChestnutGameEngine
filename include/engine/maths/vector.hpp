#ifndef __CHESTNUT_VECTOR_H__
#define __CHESTNUT_VECTOR_H__

#include <cmath>
#include <string>

namespace chestnut
{
    template< typename T >
    struct Vector2
    {
        T x, y;

        Vector2() : x(0), y(0) {}
        Vector2( T _x, T _y ) : x(_x), y(_y) {} 

        T getMagnitude() const;

        void normalize();

        void negate();

        void add( const Vector2& other );
        void operator+=( const Vector2& other );

        void subtract( const Vector2& other );
        void operator-=( const Vector2& other );

        void multiplyByScalar( const T s );
        void operator*=( const T s );

        T multiplyByVecDot( const Vector2<T>& other ) const;

        template< typename U >
        operator Vector2<U>() const;
    };

    template< typename T >
    template< typename U >
    Vector2<T>::operator Vector2<U>() const
    {
        return { static_cast<U>(x), static_cast<U>(y) };
    }

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

    template< typename T >
    T operator*( Vector2<T> v1, Vector2<T> v2 ) = delete; // forbidden due to ambiguity between dot and cross product

    // predefined vectors //
    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
    typedef Vector2<double> Vector2lf;

    #define VEC_TO_STR( v ) ( "[ " + std::to_string( v.x ) + ", " + std::to_string( v.y ) + " ]" )

} // namespace chestnut

#endif // __CHESTNUT_VECTOR_H__
