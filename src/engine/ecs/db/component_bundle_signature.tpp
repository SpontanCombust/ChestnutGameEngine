namespace chestnut
{    
    template< typename T >
    void SComponentBundleSignature::add() 
    {
        add( TINDEX(T) );
    }

    template< typename T >
    void SComponentBundleSignature::remove() 
    {
        remove( TINDEX(T) );
    }

    template< typename T >
    bool SComponentBundleSignature::includes() const
    {
        return includes( TINDEX(T) );
    }

} // namespace chestnut
