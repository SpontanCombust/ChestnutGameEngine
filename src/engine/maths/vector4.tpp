#include "vector2.hpp"
#include "vector3.hpp"

namespace chestnut
{    
    template<typename T>
    Vector4<T>::Vector4() 
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
        w = 1.0;
    }

    template<typename T>
    Vector4<T>::Vector4( T _x, T _y, T _z, T _w ) 
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    template<typename T>
    Vector4<T>& Vector4<T>::operator+=( const Vector4<T>& v ) 
    {
        *this = vec4Sum( *this, v );
        return *this;
    }

    template<typename T>
    Vector4<T>& Vector4<T>::operator-=( const Vector4<T>& v ) 
    {
        *this = vec4Difference( *this, v );
        return *this;
    }

    template<typename T>
    Vector4<T>& Vector4<T>::operator*=( T s ) 
    {
        *this = vec4ScalarProduct( *this, s );
        return *this;
    }

    template<typename T>
    std::string Vector4<T>::toString() const
    {
        return "[ " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + " ]";
    }

    template< typename T >
    template< typename U >
    Vector4<T>::operator Vector4<U>() const
    {
        return { static_cast<U>(x), static_cast<U>(y), static_cast<U>(z), static_cast<U>(w) };
    }

    template<typename T>
    Vector4<T>::operator Vector2<T>() const
    {
        return vec4ToVec2<T>( *this );
    }

    template<typename T>
    Vector4<T>::operator Vector3<T>() const
    {
        return vec4ToVec3<T>( *this );
    }



    template< typename T >
    Vector4<T> vec4Negated( const Vector4<T>& v )
    {
        Vector4<T> v1;
        v1.x = -v.x;
        v1.y = -v.y;
        v1.z = -v.z;
        v1.w = -v.w;
        return v1;
    }

    template< typename T >
    Vector4<T> operator-( const Vector4<T>& v )
    {
        return vec4Negated(v);
    }



    template< typename T >
    Vector4<T> vec4Sum( const Vector4<T>& v1, const Vector4<T>& v2 )
    {
        Vector4<T> v3;
        v3.x = v1.x + v2.x;
        v3.y = v1.y + v2.y;
        v3.z = v1.z + v2.z;
        v3.w = v1.w + v2.w;
        return v3;
    }

    template< typename T >
    Vector4<T> operator+( const Vector4<T>& v1, const Vector4<T>& v2 )
    {
        return vec4Sum( v1, v2 );
    }



    template< typename T >
    Vector4<T> vec4Difference( const Vector4<T>& v1, const Vector4<T>& v2 )
    {
        Vector4<T> v3;
        v3.x = v1.x - v2.x;
        v3.y = v1.y - v2.y;
        v3.z = v1.z - v2.z;
        v3.w = v1.w - v2.w;
        return v3;
    }

    template<typename T>
    Vector4<T> operator-( const Vector4<T>& v1, const Vector4<T>& v2 )
    {
        return vec4Difference( v1, v2 );
    }



    template< typename T >
    Vector4<T> vec4ScalarProduct( const Vector4<T>& v, T s )
    {
        Vector4<T> v1;
        v1.x = v.x * s;
        v1.y = v.y * s;
        v1.z = v.z * s;
        v1.w = v.w * s;
        return v1;
    }

    template< typename T >
    Vector4<T> operator*( T s, const Vector4<T>& v )
    {
        return vec4ScalarProduct( v, s );
    }

    template< typename T >
    Vector4<T> operator*( const Vector4<T>& v, T s )
    {
        return vec4ScalarProduct( v, s );
    }



    template< typename T >
    Vector4<T> vec4LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector4<T>& v )
    {
        Vector4<T> v1;

        v1.x = m.get(0,0) * v.x + m.get(0,1) * v.y + m.get(0,2) * v.z + m.get(0,3) * v.w;
        v1.y = m.get(1,0) * v.x + m.get(1,1) * v.y + m.get(1,2) * v.z + m.get(1,3) * v.w;
        v1.z = m.get(2,0) * v.x + m.get(2,1) * v.y + m.get(2,2) * v.z + m.get(2,3) * v.w;
        v1.w = m.get(3,0) * v.x + m.get(3,1) * v.y + m.get(3,2) * v.z + m.get(3,3) * v.w;

        return v1;
    }

    template< typename T >
    Vector4<T> operator*( const Matrix4<T>& m, const Vector4<T>& v )
    {
        return vec4LeftMultiplyByMatrix( m, v );
    }



    template< typename T >
    Vector2<T> vec4ToVec2( const Vector4<T>& v )
    {
        Vector2<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        return v1;
    }

    template< typename T >
    Vector3<T> vec4ToVec3( const Vector4<T>& v )
    {
        Vector3<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        v1.z = v.z;
        return v1;
    }

} // namespace chestnut
