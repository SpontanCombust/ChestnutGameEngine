namespace chestnut
{
    template< typename T >
    bool CComponentDatabase::hasComponentsType() const
    {
        if( m_componentMaps.find( TINDEX(T) ) != m_componentMaps.end() )
            return true;
        return false;
    }
    
    template< typename T >
    bool CComponentDatabase::hasComponent( entityid_t id ) const
    {
        if( !hasComponentsType<T>() )
            return false;

        auto& typedCompMap = m_componentMaps.at( TINDEX(T) );
        if( typedCompMap.find( id ) != typedCompMap.end() )
            return true;
        return false;
    }
    
    template< typename T >
    T& CComponentDatabase::getComponent( entityid_t id ) const
    {
        if( !hasComponentsType<T>() )
        {
            throw ChestnutException( "No component with that type found!" );
        }

        auto& typedCompMap = m_componentMaps.at( TINDEX(T) );

        bool found = false;
        entityid_t  pair_id;
        IComponent *pair_component;
        for( auto& pair : typedCompMap )
        {
            pair_id = pair.first;
            pair_component = pair.second;

            if( pair_id == id )
            {
                found = true;
                break;
            }
        }

        if( found )
        {
            return *dynamic_cast<T*>( pair_component );
        }
        else
        {
            throw ChestnutException( "No component with that type and ID found!" );
        }
    }
    
    template< typename T >
    bool CComponentDatabase::eraseComponent( entityid_t id, bool shouldDelete ) 
    {
        if( !hasComponent<T>( id ) )
            return false;

        std::type_index tindex = TINDEX(T);
        
        if( shouldDelete )
        {
            IComponent *component = m_componentMaps[tindex][id];
            delete component;
            component = nullptr;
        }
        m_componentMaps[tindex].erase( id );

        if( m_componentMaps[tindex].empty() )
            m_componentMaps.erase( tindex );

        return true;
    }
    
    template< typename T >
    std::unordered_map< entityid_t, T* > CComponentDatabase::getComponentMapOfType() const
    {
        std::unordered_map< entityid_t, IComponent* > typedCompMap;
        std::unordered_map< entityid_t, T* > typedCastedCompMap;

        // if has no components of that type, return empty map
        if( !hasComponentsType<T>() )
        {
            return typedCastedCompMap;
        }

        typedCompMap = m_componentMaps.at( TINDEX(T) );
        for( const auto &pair : typedCompMap )
        {
            const entityid_t &id = pair.first;
            IComponent *component = pair.second;

            typedCastedCompMap[id] = dynamic_cast<T*>( component );
        }

        return typedCastedCompMap;
    }

} // namespace chestnut
