namespace chestnut
{
    template<typename T >
    Vector<T,3>::Vector()
    : data{0}
    {

    }

    template<typename T>
    Vector<T,3>::Vector( T init ) 
    : data{ init, init, init }
    {
        
    }

    template<typename T>
    Vector<T,3>::Vector( T _x, T _y, T _z )
    : data{ _x, _y, _z }
    {

    }

    template<typename T>
    T& Vector<T,3>::x() 
    {
        return data[0];
    }

    template<typename T>
    const T& Vector<T,3>::x() const
    {
        return data[0];
    }

    template<typename T>
    T& Vector<T,3>::y() 
    {
        return data[1];
    }

    template<typename T>
    const T& Vector<T,3>::y() const
    {
        return data[1];
    }

    template<typename T>
    T& Vector<T,3>::z() 
    {
        return data[2];
    }

    template<typename T>
    const T& Vector<T,3>::z() const
    {
        return data[2];
    }

    template<typename T>
    T& Vector<T,3>::operator[]( size_t i ) 
    {
        if( i >= 3 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
    }

    template<typename T>
    T Vector<T,3>::operator[]( size_t i ) const
    {
        if( i >= 3 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
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
    Vector<T,3>& Vector<T,3>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,3>( *this, s );
        return *this;
    }

    template<typename T>
    std::string Vector<T,3>::toString() const
    {
        std::string str;

        str += "[ ";
        str += std::to_string(data[0]) + ", " + std::to_string(data[1]) + ", " + std::to_string(data[2]);
        str += " ]";
        
        return str;
    }



    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,2>& v1, const Vector<T,2>& v2 )
    {
        Vector<T,3> pv;
        pv.data[0] = 0.0;
        pv.data[1] = 0.0;
        pv.data[2] = v1.x() * v2.y() - v1.y() * v2.x();
        return pv;   
    }

    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,3>& v1, const Vector<T,3>& v2 )
    {
        Vector<T,3> pv;
        pv.data[0] = v1.y() * v2.z() - v1.z() * v2.y();
        pv.data[1] = v1.z() * v2.x() - v1.x() * v2.z();
        pv.data[2] = v1.x() * v2.y() - v1.y() * v2.x();
        return pv;
    }

} // namespace chestnut
