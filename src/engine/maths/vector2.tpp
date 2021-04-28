#include <cstring>

namespace chestnut
{
    template<typename T >
    Vector<T,2>::Vector()
    : data{0},
      x( data[0] ), y( data[1] )
    {

    }

    template<typename T>
    Vector<T,2>::Vector( const Vector<T,2>& v )
    : x( data[0] ), y( data[1] )
    {
        std::memcpy( data, v.data, sizeof( data ) );
    }

    template<typename T>
    Vector<T,2>::Vector( T init ) 
    : data{ init },
      x( data[0] ), y( data[1] )
    {

    }

    template<typename T>
    Vector<T,2>::Vector( T _x, T _y )
    : data{ _x, _y },
      x( data[0] ), y( data[1] )
    {

    }

    template<typename T>
    Vector<T,2>& Vector<T,2>::operator=( const Vector<T,2>& v ) 
    {
        std::memcpy( data, v.data, sizeof( data ) );
        return *this;
    }

    template<typename T>
    T& Vector<T,2>::operator[]( size_t i ) 
    {
        if( i >= 2 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
    }

    template<typename T>
    T Vector<T,2>::operator[]( size_t i ) const
    {
        if( i >= 2 )
        {
            throw ChestnutException( "Vector index out of bounds!" );
        }
        
        return data[i];
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
    Vector<T,2>& Vector<T,2>::operator*=( T s ) 
    {
        *this = vecScalarProduct<T,2>( *this, s );
        return *this;
    }

    template<typename T>
    std::string Vector<T,2>::toString() const
    {
        std::string str;

        str += "[ ";
        str += std::to_string(x) + ", " + std::to_string(y);
        str += " ]";
        
        return str;
    }

} // namespace chestnut
