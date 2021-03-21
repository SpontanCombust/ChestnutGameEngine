namespace chestnut
{
    template< typename T >
    T& CEntityManager::createComponent( entityid_t id ) 
    {
        if( m_componentDB.hasComponent<T>( id ) )
        {
            return m_componentDB.getComponent<T>( id );
        }
        else
        {
            T *component = new T();
            component->ownerID = id;
            m_componentDB.pushComponent( component );
            m_typesOfRecentComponents.push_front( TINDEX(T) );
            return *component;
        }
    }
    
} // namespace chestnut
