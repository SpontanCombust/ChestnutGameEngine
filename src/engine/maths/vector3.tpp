#include <cmath>

#include "vector2.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"

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

    template<typename T>
    Vector3<T>& Vector3<T>::operator+=( const Vector3<T>& v ) 
    {
        *this = vec3Sum<T>( *this, v );
        return *this;
    }

    template<typename T>
    Vector3<T>& Vector3<T>::operator-=( const Vector3<T>& v ) 
    {
        *this = vec3Difference<T>( *this, v );
        return *this;
    }

    template<typename T>
    Vector3<T>& Vector3<T>::operator*=( T s ) 
    {
        *this = vec3ScalarProduct<T>( *this, s );
        return *this;
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

    template<typename T>
    Vector3<T>::operator Vector2<T>() const
    {
        return vec3ToVec2<T>( *this );
    }

    template<typename T>
    Vector3<T>::operator Vector4<T>() const
    {
        return vec3ToVec4<T>( *this );
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
            T mag = vec3Magnitude<T>(v);
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
        return vec3Negated<T>(v);
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
        return vec3Sum<T>( v1, v2 );
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
        return vec3Difference<T>( v1, v2 );
    }



    template< typename T >
    Vector3<T> vec3ScalarProduct( const Vector3<T>& v, T s ) 
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
        return vec3ScalarProduct<T>( v, s );
    }

    template< typename T >
    Vector3<T> operator*( const Vector3<T>& v, T s ) 
    {
        return vec3ScalarProduct<T>( v, s );
    }



    template< typename T >
    T vec3DotProduct( const Vector3<T>& v1, const Vector3<T>& v2 ) 
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template< typename T >
    Vector3<T> vec3CrossProduct( const Vector3<T>& v1, const Vector3<T>& v2 )
    {
        Vector3<T> pv;
        pv.x = v1.y * v2.z - v1.z * v2.y;
        pv.y = v1.z * v2.x - v1.x * v2.z;
        pv.z = v1.x * v2.y - v1.y * v2.x;
        return pv;
    }



    template<typename T>
    Vector3<T> vec3LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector3<T>& v ) 
    {
        Vector3<T> v1;

        v1.x = m.get(0,0) * v.x + m.get(0,1) * v.y + m.get(0,2) * v.z + m.get(0,3);
        v1.y = m.get(1,0) * v.x + m.get(1,1) * v.y + m.get(1,2) * v.z + m.get(1,3);
        v1.z = m.get(2,0) * v.x + m.get(2,1) * v.y + m.get(2,2) * v.z + m.get(2,3);

        return v1;
    }

    template< typename T >
    Vector3<T> operator*( const Matrix4<T>& lhs, const Vector3<T>& rhs )
    {
        return vec3LeftMultiplyByMatrix<T>( lhs, rhs );
    }

    template< typename T >
    Vector3<T> vec3Translate( const Vector3<T>& v, T tx, T ty, T tz )
    {
        Matrix4<T> m = mat4MakeTranslation<T>( tx, ty, tz);
        Vector3<T> v1 = vec3LeftMultiplyByMatrix<T>( v, m );

        return v1;
    }

    template< typename T >
    Vector3<T> vec3Scale( const Vector3<T>& v, T sx, T sy, T sz )
    {
        Matrix4<T> m = mat4MakeScale<T>( sx, sy, sz );
        Vector3<T> v1 = vec3LeftMultiplyByMatrix<T>( v, m );

        return v1;
    }

    template< typename T >
    Vector3<T> vec3Rotate( const Vector3<T>& v, Vector3<T> axis, double angleRad )
    {
        axis = vec3Normalized<T>( axis );

        Matrix4<T> m = mat4MakeRotation<T>( axis, angleRad );
        Vector3<T> v1 = vec3LeftMultiplyByMatrix( v, m );

        return v1;
    }



    template< typename T >
    Vector2<T> vec3ToVec2( const Vector3<T>& v )
    {
        Vector2<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        return v1;
    }

    template< typename T >
    Vector4<T> vec3ToVec4( const Vector3<T>& v, T w )
    {
        Vector4<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        v1.z = v.z;
        v1.w = w;
        return v1;
    }

} // namespace chestnut
