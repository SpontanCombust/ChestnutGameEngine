namespace chestnut
{    
    template<typename T >
    Vector<T,4>::Vector()
    : data{0}
    {

    }
    
    template<typename T>
    Vector<T,4>::Vector( T init ) 
    : data{ init, init, init, init }
    {
        
    }

    template<typename T>
    Vector<T,4>::Vector( T _x, T _y, T _z, T _w )
    : data{ _x, _y, _z, _w }
    {

    }

    template<typename T>
    T& Vector<T,4>::x() 
    {
        return data[0];
    }

    template<typename T>
    const T& Vector<T,4>::x() const
    {
        return data[0];
    }

    template<typename T>
    T& Vector<T,4>::y() 
    {
        return data[1];
    }

    template<typename T>
    const T& Vector<T,4>::y() const
    {
        return data[1];
    }

    template<typename T>
    T& Vector<T,4>::z() 
    {
        return data[2];
    }

    template<typename T>
    const T& Vector<T,4>::z() const
    {
        return data[2];
    }

    template<typename T>
    T& Vector<T,4>::w() 
    {
        return data[3];
    }

    template<typename T>
    const T& Vector<T,4>::w() const
    {
        return data[3];
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
        str += std::to_string(data[0]) + ", " + std::to_string(data[1]) + ", " + std::to_string(data[2]) + ", " + std::to_string(data[3]);
        str += " ]";
        
        return str;
    }

} // namespace chestnut
