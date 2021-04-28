namespace chestnut
{
    template<typename T >
    Vector<T,3>::Vector()
    : data{0},
      x( data[0] ), y( data[1] ), z( data[2] )
    {

    }

    template<typename T>
    Vector<T,3>::Vector( const Vector<T,3>& v )
    : x( data[0] ), y( data[1] ), z( data[2] )
    {
        std::memcpy( data, v.data, sizeof( data ) );
    }

    template<typename T>
    Vector<T,3>::Vector( T init ) 
    : data{ init },
      x( data[0] ), y( data[1] ), z( data[2] )
    {

    }

    template<typename T>
    Vector<T,3>::Vector( T _x, T _y, T _z )
    : data{ _x, _y, _z },
      x( data[0] ), y( data[1] ), z( data[2] )
    {

    }

    template<typename T>
    Vector<T,3>& Vector<T,3>::operator=( const Vector<T,3>& v ) 
    {
        std::memcpy( data, v.data, sizeof( data ) );
        return *this;
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
        str += std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
        str += " ]";
        
        return str;
    }



    template< typename T >
    Vector<T,3> vecCrossProduct( const Vector<T,2>& v1, const Vector<T,2>& v2 )
    {
        Vector<T,3> pv;
        pv.data[0] = 0.0;
        pv.data[1] = 0.0;
        pv.data[2] = v1.x * v2.y - v1.y * v2.x;
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

} // namespace chestnut
