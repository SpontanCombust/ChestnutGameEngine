#include <cmath>

#include "vector3.hpp"
#include "matrix4.hpp"

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

    template<typename T>
    Vector2<T>& Vector2<T>::operator+=( const Vector2<T>& v ) 
    {
        *this = vec2Sum<T>( *this, v );
        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator-=( const Vector2<T>& v ) 
    {
        *this = vec2Difference<T>( *this, v );
        return *this;
    }

    template<typename T>
    Vector2<T>& Vector2<T>::operator*=( T s ) 
    {
        *this = vec2ScalarProduct<T>( *this, s );
        return *this;
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

    template<typename T>
    Vector2<T>::operator Vector3<T>() const
    {
        return vec2ToVec3( *this );
    }

    template<typename T>
    Vector2<T>::operator Vector4<T>() const
    {
        return vec2ToVec4( *this );
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
            T mag = vec2Magnitude<T>(v);
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
        return vec2Negated<T>(v);
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
        return vec2Sum<T>( v1, v2 );
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
        return vec2Difference<T>( v1, v2 );
    }



    template< typename T >
    Vector2<T> vec2ScalarProduct( const Vector2<T>& v, T s ) 
    {
        Vector2<T> v1;
        v1.x = v.x * s;
        v1.y = v.y * s;
        return v1;
    }

    template< typename T >
    Vector2<T> operator*( T s, const Vector2<T>& v ) 
    {
        return vec2ScalarProduct<T>( v, s );
    }

    template< typename T >
    Vector2<T> operator*( const Vector2<T>& v, T s ) 
    {
        return vec2ScalarProduct<T>( v, s );
    }



    template< typename T >
    T vec2DotProduct( const Vector2<T>& v1, const Vector2<T>& v2 ) 
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template< typename T >
    Vector3<T> vec2CrossProduct( const Vector2<T>& v1, const Vector2<T>& v2 )
    {
        Vector3<T> pv;
        pv.x = 0.0;
        pv.y = 0.0;
        pv.z = v1.x * v2.y - v1.y * v2.x;
        return pv;   
    }
    


    template< typename T >
    Vector2<T> vec2LeftMultiplyByMatrix( const Matrix4<T>& m, const Vector2<T>& v ) 
    {
        Vector2<T> v1;

        v1.x = m.get(0,0) * v.x + m.get(0,1) * v.y + m.get(0,3);
        v1.y = m.get(1,0) * v.x + m.get(1,1) * v.y + m.get(1,3);

        return v1;
    }

    template< typename T >
    Vector2<T> operator*( const Matrix4<T>& lhs, const Vector2<T>& rhs )
    {
        return vec2LeftMultiplyByMatrix<T>( lhs, rhs );
    }

    template< typename T >
    Vector2<T> vec2Translate( const Vector2<T>& v, T tx, T ty )
    {
        Matrix4<T> m = mat4MakeTranslation<T>( tx, ty, 0.0 );
        Vector2<T> v1 = vec2LeftMultiplyByMatrix<T>( v, m );

        return v1;
    }

    template< typename T >
    Vector2<T> vec2Scale( const Vector2<T>& v, T sx, T sy )
    {
        Matrix4<T> m = mat4MakeScale<T>( sx, sy, 1.0 );
        Vector2<T> v1 = vec2LeftMultiplyByMatrix<T>( v, m );

        return v1;
    }

    template< typename T >
    Vector2<T> vec2Rotate( const Vector2<T>& v, double angleRad )
    {
        Matrix4<T> m = mat4MakeRotationZ<T>( angleRad );
        Vector2<T> v1 = vec2LeftMultiplyByMatrix<T>( v, m );

        return v1;
    }
    


    template< typename T >
    Vector3<T> vec2ToVec3( const Vector2<T>& v, T z )
    {
        Vector3<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        v1.z = z;
        return v1;
    }

    template< typename T >
    Vector4<T> vec2ToVec4( const Vector2<T>& v, T z, T w )
    {
        Vector4<T> v1;
        v1.x = v.x;
        v1.y = v.y;
        v1.z = z;
        v1.w = w;
        return v1;
    }

} // namespace chestnut
