#include <algorithm>
#include <cstring>

namespace chestnut::engine
{
    template<typename T>
    Vector<T,2>::Vector()
    {
        x = y = 0;
    }

    template<typename T>
    Vector<T,2>::Vector( T init ) 
    {
        x = y = init;
    }

    template<typename T>
    Vector<T,2>::Vector( T _x, T _y ) 
    {
        x = _x;
        y = _y;
    }

    template<typename T>
    T* Vector<T,2>::data()
    {
        return &x;
    }

    template<typename T>
    const T* Vector<T,2>::data() const
    {
        return &x;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator+=( const Vector<T,2>& v ) 
    {
        *this = vecSum<T,2>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator-=( const Vector<T,2>& v ) 
    {
        *this = vecDifference<T,2>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator*=( const Vector<T,2>& v ) 
    {
        *this = vecComponentProduct<T,2>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator/=( const Vector<T,2>& v ) 
    {
        *this = vecComponentQuotient<T,2>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,2>( *this, s );
        return *this;
    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator/=( T s ) 
    {
        *this = vecScalarQuotient<T,2>( *this, s );
        return *this;
    }

} // namespace chestnut::engine
