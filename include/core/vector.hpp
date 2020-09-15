#pragma once

template< typename T >
struct Vector2
{
    T x, y;

    Vector2() : x(0), y(0) {}
    Vector2( T _x, T _y ) : x(_x), y(_y) {} 

    T getMagnitude() const;

    void normalize();

    void negate();
    void operator-();

    void add( const Vector2& other );
    void operator+=( const Vector2& other );
    Vector2 operator+( const Vector2& other ) const;

    void subtract( const Vector2& other );
    void operator-=( const Vector2& other );
    Vector2 operator-( const Vector2& other ) const;

    void multiplyByScalar( const T s );
    void operator*=( const T s );

    T multiplyDot( const Vector2<T>& other ) const;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
