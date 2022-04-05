namespace chestnut::engine
{
    template<typename T>
    Vector<T,3>::Vector()
    {
        x = y = z = 0;
    }

    template<typename T>
    Vector<T,3>::Vector( T init ) 
    {
        x = y = z = init;
    }

    template<typename T>
    Vector<T,3>::Vector( T _x, T _y, T _z ) 
    {
        x = _x;
        y = _y;
        z = _z;
    }

    template<typename T>
    T* Vector<T,3>::data()
    {
        return &x;
    }

    template<typename T>
    const T* Vector<T,3>::data() const
    {
        return &x;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator+=( const Vector<T,3>& v ) 
    {
        *this = vecSum<T,3>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator-=( const Vector<T,3>& v ) 
    {
        *this = vecDifference<T,3>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator*=( const Vector<T,3>& v ) 
    {
        *this = vecComponentProduct<T,3>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator/=( const Vector<T,3>& v ) 
    {
        *this = vecComponentQuotient<T,3>( *this, v );
        return *this;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,3>( *this, s );
        return *this;
    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator/=( T s ) 
    {
        *this = vecScalarQuotient<T,3>( *this, s );
        return *this;
    }



    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,2>& v1, const Vector<T,2>& v2 )
    {
        Vector<T,3> pv;

        pv.x = 0.0;
        pv.y = 0.0;
        pv.z = v1.x * v2.y - v1.y * v2.x;
        return pv;   
    }

    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,3>& v1, const Vector<T,3>& v2 )
    {
        Vector<T,3> pv;
        pv.x = v1.y * v2.z - v1.z * v2.y;
        pv.y = v1.z * v2.x - v1.x * v2.z;
        pv.z = v1.x * v2.y - v1.y * v2.x;
        return pv;
    }

} // namespace chestnut::engine
