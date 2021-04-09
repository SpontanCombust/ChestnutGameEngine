namespace chestnut
{    
    template< typename T >
    SComponentSetSignature& SComponentSetSignature::add() 
    {
        return add( TINDEX(T) );
    }

    template< typename T >
    SComponentSetSignature& SComponentSetSignature::remove() 
    {
        return remove( TINDEX(T) );
    }

    template< typename T >
    bool SComponentSetSignature::includes() const
    {
        return includes( TINDEX(T) );
    }

} // namespace chestnut
