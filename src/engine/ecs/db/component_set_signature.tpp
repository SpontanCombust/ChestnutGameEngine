namespace chestnut
{    
    template< typename T >
    void SComponentSetSignature::add() 
    {
        add( TINDEX(T) );
    }

    template< typename T >
    void SComponentSetSignature::remove() 
    {
        remove( TINDEX(T) );
    }

    template< typename T >
    bool SComponentSetSignature::includes() const
    {
        return includes( TINDEX(T) );
    }

} // namespace chestnut
