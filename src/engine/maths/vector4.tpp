namespace chestnut
{    
    template<typename T >
    Vector<T,4>::Vector()
    : data{0},
      x( data[0] ), y( data[1] ), z( data[2] ), w( data[3] )
    {

    }
    
    template<typename T>
    Vector<T,4>::Vector( const Vector<T,4>& v )
    : x( data[0] ), y( data[1] ), z( data[2] ), w( data[3] )
    {
        std::memcpy( data, v.data, sizeof( data ) );
    }

    template<typename T>
    Vector<T,4>::Vector( T init ) 
    : data{ init },
      x( data[0] ), y( data[1] ), z( data[2] ), w( data[3] )
    {

    }

    template<typename T>
    Vector<T,4>::Vector( T _x, T _y, T _z, T _w )
    : data{ _x, _y, _z, _w },
      x( data[0] ), y( data[1] ), z( data[2] ), w( data[3] )
    {

    }

    template<typename T>
    Vector<T,4>& Vector<T,4>::operator=( const Vector<T,4>& v ) 
    {
        std::memcpy( data, v.data, sizeof( data ) );
        return *this;
    }

    template<typename T>
    T& Vector<T,4>::operator[]( size_t i ) 
    {
        if( i >= 4 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
    }

    template<typename T>
    T Vector<T,4>::operator[]( size_t i ) const
    {
        if( i >= 4 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
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
    Vector<T,4>& Vector<T,4>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,4>( *this, s );
        return *this;
    }

    template<typename T>
    std::string Vector<T,4>::toString() const
    {
        std::string str;

        str += "[ ";
        str += std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
        str += " ]";
        
        return str;
    }

} // namespace chestnut
