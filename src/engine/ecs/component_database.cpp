#include "component_database.hpp"

namespace chestnut
{   
    bool CComponentDatabase::pushComponent( IComponent *component ) 
    {
        if( !component )
            return false;
        else if( component->parentGUID == GUID_UNREGISTERED )
        {
            LOG_CHANNEL( "COMPONENT_DB", "Given component has unregistered GUID!" );
            return false;
        }
            
        std::type_index tindex = std::type_index( typeid( *component ) );
        guid_t guid = component->parentGUID;

        auto& typedCompMap = m_componentMaps[ tindex ];
        if( typedCompMap.find( guid ) != typedCompMap.end() )
        {
            LOG_CHANNEL( "COMPONENT_DB", "Database already has component of that type and GUID!" );
            return false;
        }
        else
        {
            m_componentMaps[ tindex ][ guid ] = component;
            return true;
        }
    }
    
    bool CComponentDatabase::eraseComponents( guid_t guid, bool shouldDelete ) 
    {
        bool foundAndErased = false;
        for( auto& pair : m_componentMaps )
        {
            const auto& tindex = pair.first;
            auto& typedComponentMap = pair.second;

            auto it = typedComponentMap.find( guid );
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
