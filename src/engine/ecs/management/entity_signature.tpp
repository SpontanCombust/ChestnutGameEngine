namespace chestnut
{    
    template< typename T >
    CEntitySignature& CEntitySignature::add() 
    {
        return add( TINDEX(T) );
    }

    template< typename T >
    CEntitySignature& CEntitySignature::remove() 
    {
        return remove( TINDEX(T) );
    }

    template< typename T >
    bool CEntitySignature::includes() const
    {
        return includes( TINDEX(T) );
    }

} // namespace chestnut
