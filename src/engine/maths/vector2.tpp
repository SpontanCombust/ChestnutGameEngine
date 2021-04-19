#include <cmath>

namespace chestnut
{
    template< typename T >
    Vector2<T>::Vector2()
    {
        x = 0;
        y = 0;
    }

    template< typename T >
    Vector2<T>::Vector2( T _x, T _y ) 
    {
        x = _x;
        y = _y;
    }

    template< typename T >
    std::string Vector2<T>::toString() const
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + " ]";
    }

    template< typename T >
    template< typename U >
    Vector2<T>::operator Vector2<U>() const
    {
        return { static_cast<U>(x), static_cast<U>(y) };
    }



    template< typename T >
    T vec2Magnitude( const Vector2<T>& v )
    {
        return sqrt( v.x * v.x + v.y * v.y );
    }



    template< typename T >
    Vector2<T> vec2Normalized( const Vector2<T>& v )
    {
        Vector2<T> v1 = v;
        if( v1.x != 0.0 && v1.y != 0.0 )
        {
            T mag = vec2Magnitude(v);
            v1.x /= mag;
            v1.y /= mag;
        }
        return v1;
    }



    template< typename T >
    Vector2<T> vec2Negated( const Vector2<T>& v ) 
    {
        Vector2<T> v1;
        v1.x = -v.x;
        v1.y = -v.y;
        return v1;
    }

    template< typename T >
    Vector2<T> operator-( const Vector2<T>& v ) 
    {
        return vec2Negated(v);
    }



    template< typename T >
    Vector2<T> vec2Sum( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        Vector2<T> v3;
        v3.x = v1.x + v2.x;
        v3.y = v1.y + v2.y;
        return v3;
    }

    template< typename T >
    Vector2<T> operator+( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        return vec2Sum( v1, v2 );
    }



    template< typename T >
    Vector2<T> vec2Difference( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        Vector2<T> v3;
        v3.x = v1.x - v2.x;
        v3.y = v1.y - v2.y;
        return v3;
    }

    template<typename T>
    Vector2<T> operator-( const Vector2<T>& v1, const Vector2<T>& v2 )
    {
        return vec2Difference( v1, v2 );
    }



    template< typename T >
    Vector2<T> vec2Scaled( const Vector2<T>& v, T s ) 
    {
        Vector2<T> v1;
        v1.x = v.x * s;
        v1.y = v.y * s;
        return v1;
    }

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v ) 
    {
        return vec2Scaled( v, s );
    }

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s ) 
    {
        return vec2Scaled( v, s );
    }



    template< typename T >
    T vec2DotProduct( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
   
} // namespace chestnut
