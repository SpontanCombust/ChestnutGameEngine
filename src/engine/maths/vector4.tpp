namespace chestnut
{    
    template<typename T>
    Vector<T,4>::Vector()
    {
        x = y = z = w = 0;
    }

    template<typename T>
    Vector<T,4>::Vector( T init ) 
    {
        x = y = z = w = init;
    }

    template<typename T>
    Vector<T,4>::Vector( T _x, T _y, T _z, T _w ) 
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    template<typename T>
    T* Vector<T,4>::data()
    {
        return &x;
    }

    template<typename T>
    const T* Vector<T,4>::data() const
    {
        return &x;
    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator+=( const Vector<T,4>& v ) 
    {
        *this = vecSum<T,4>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator-=( const Vector<T,4>& v ) 
    {
        *this = vecDifference<T,4>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator*=( const Vector<T,4>& v ) 
    {
        *this = vecComponentProduct<T,4>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator/=( const Vector<T,4>& v ) 
    {
        *this = vecComponentQuotient<T,4>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,4>( *this, s );
        return *this;
    }

} // namespace chestnut
