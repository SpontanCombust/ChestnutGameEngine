#include "component_database.hpp"

namespace chestnut
{   
    void CComponentDatabase::pushComponent( IComponent *component ) 
    {
        if( !component )
        {
            throw ChestnutException( "Can't push null component to database!" );
        }
        else if( component->ownerID == ENTITY_ID_INVALID )
        {
            throw ChestnutException( "Can't push component with unregistered owner ID to database!" );
        }
            
        std::type_index tindex = TINDEX( *component );
        entityid_t id = component->ownerID;

        auto& typedCompMap = m_componentMaps[ tindex ];
        if( typedCompMap.find( id ) != typedCompMap.end() )
        {
            throw ChestnutException( "Entity can have only one copy of component of given type!" );
        }
        else
        {
            m_componentMaps[ tindex ][ id ] = component;
        }
    }
    
    bool CComponentDatabase::eraseComponents( entityid_t id, bool shouldDelete ) 
    {
        bool foundAndErased = false;
        for( auto& pair : m_componentMaps )
        {
            const auto& tindex = pair.first;
            auto& typedComponentMap = pair.second;

            auto it = typedComponentMap.find( id );
            if( it != typedComponentMap.end() )
            {
                if( shouldDelete )
                {
                    IComponent *component = (*it).second;
                    delete component;
                    component = nullptr;
                }
                typedComponentMap.erase( it );
                foundAndErased = true;
            }

            if( typedComponentMap.empty() )
                m_componentMaps.erase( tindex );
        }
        
        return foundAndErased;
    }

    void CComponentDatabase::clearComponents() 
    {
        for( auto& pair : m_componentMaps )
        {
            auto& typedComponentsMap = pair.second;

            IComponent *component;
            for( auto& typedPair : typedComponentsMap )
            {
                component = typedPair.second;
                delete component;
                component = nullptr;
            }
            typedComponentsMap.clear();
        }
        m_componentMaps.clear();
    }

} // namespace chestnut
