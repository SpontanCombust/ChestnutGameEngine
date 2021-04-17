#include <cmath>

namespace chestnut
{
    template< typename T >
    Vector3<T>::Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }

    template< typename T >
    Vector3<T>::Vector3( T _x, T _y, T _z ) 
    {
        x = _x;
        y = _y;
        z = _z;
    }

    template< typename T >
    std::string Vector3<T>::toString() const
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + " ]";
    }

    template< typename T >
    template< typename U >
    Vector3<T>::operator Vector3<U>() const
    {
        return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(z) };
    }



    template< typename T >
    T vec3Magnitude( const Vector3<T>& v )
    {
        return sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
    }



    template< typename T >
    Vector3<T> vec3Normalized( const Vector3<T>& v )
    {
        Vector3<T> v1 = v;
        if( v1.x != 0 && v1.y != 0 && v1.z != 0 )
        {
            T mag = vec2Magnitude(v);
            v1.x /= mag;
            v1.y /= mag;
            v1.z /= mag;
        }
        return v1;
    }



    template< typename T >
    Vector3<T> vec3Negated( const Vector3<T>& v ) 
    {
        Vector3<T> v1;
        v1.x = -v.x;
        v1.y = -v.y;
        v1.z = -v.z;
        return v1;
    }

    template< typename T >
    Vector3<T> operator-( const Vector3<T>& v ) 
    {
        return vec3Negated(v);
    }



    template< typename T >
    Vector3<T> vec3Sum( const Vector3<T>& v1, const Vector3<T>& v2 ) 
    {
        Vector3<T> v3;
        v3.x = v1.x + v2.x;
        v3.y = v1.y + v2.y;
        v3.z = v1.z + v2.z;
        return v3;
    }

    template< typename T >
    Vector3<T> operator+( const Vector3<T>& v1, const Vector3<T>& v2 ) 
    {
        return vec3Sum( v1, v2 );
    }



    template< typename T >
    Vector3<T> vec3Difference( const Vector3<T>& v1, const Vector3<T>& v2 ) 
    {
        Vector3<T> v3;
        v3.x = v1.x - v2.x;
        v3.y = v1.y - v2.y;
        v3.z = v1.z - v2.z;
        return v3;
    }

    template<typename T>
    Vector3<T> operator-( const Vector3<T>& v1, const Vector3<T>& v2 )
    {
        return vec3Difference( v1, v2 );
    }



    template< typename T >
    Vector3<T> vec3Scaled( const Vector3<T>& v, T s ) 
    {
        Vector3<T> v1;
        v1.x = v.x * s;
        v1.y = v.y * s;
        v1.z = v.z * s;
        return v1;
    }

    template< typename T >
    Vector3<T> operator*( T s, const Vector3<T>& v ) 
    {
        return vec3Scaled( v, s );
    }

    template< typename T >
    Vector3<T> operator*( const Vector3<T>& v, T s ) 
    {
        return vec3Scaled( v, s );
    }



    template< typename T >
    T vec3DotProduct( const Vector3<T>& v1, const Vector3<T>& v2 ) 
    {
        return v1.x * v2.x + v1.y * v2.y;
    }
   
} // namespace chestnut
