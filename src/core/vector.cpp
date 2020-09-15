#include "core/vector.hpp"

#include <cmath>

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
void Vector2<T>::negate() 
{
    x = -x;
    y = -y;
}

template< typename T >
void Vector2<T>::operator-() 
{
    negate();
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
Vector2<T> Vector2<T>::operator+( const Vector2<T>& other ) const
{
    return Vector2<T>( x + other.x, y + other.y );
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
Vector2<T> Vector2<T>::operator-( const Vector2<T>& other ) const
{
    return Vector2<T>( x - other.x, y - other.y );
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
T Vector2<T>::multiplyDot( const Vector2<T>& other ) const
{
    return x * other.x + y * other.y;
}
