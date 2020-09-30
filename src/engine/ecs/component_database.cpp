#include "engine/ecs/component_database.hpp"

namespace chestnut
{    
    bool CComponentDatabase::hasComponentType( std::string compTypeStr ) const
    {
        if( m_componentMaps.find( compTypeStr ) != m_componentMaps.end() )
            return true;
        return false;
    }

    bool CComponentDatabase::hasComponent( std::string compTypeStr, uint64_t guid ) const
    {
        if( !hasComponentType( compTypeStr ) )
            return false;

        auto& compMap = m_componentMaps.at( compTypeStr );
        if( compMap.find( guid ) != compMap.end() )
            return true;
        return false;
    }

    bool CComponentDatabase::pushComponent( IComponent *component ) 
    {
        if( component == nullptr )
            return false;
            
        std::string compType = component->getTypeString();
        uint64_t guid = component->parentGUID;

        if( guid == GUID_UNREGISTERED )
            return false;
        else if( hasComponent( compType, guid ) )
            return false;

        m_componentMaps[compType][guid] = component;
        return true;
    }

    IComponent* CComponentDatabase::getComponent( std::string compTypeStr, uint64_t guid ) 
    {
        if( !hasComponent( compTypeStr, guid ) )
            return nullptr;

        IComponent* component = m_componentMaps[compTypeStr][guid];

        return component;
    }

    IComponent* CComponentDatabase::pullComponent( std::string compTypeStr, uint64_t guid ) 
    {
        if( !hasComponent( compTypeStr, guid ) )
            return nullptr;

        IComponent* component = m_componentMaps[compTypeStr][guid];
        m_componentMaps[compTypeStr].erase( guid );

        return component;
    }

    void CComponentDatabase::eraseComponent( std::string compTypeStr, uint64_t guid ) 
    {
        if( !hasComponent( compTypeStr, guid ) )
            return;

        m_componentMaps[compTypeStr].erase( guid );

        if( m_componentMaps[compTypeStr].empty() )
            m_componentMaps.erase( compTypeStr );
    }

    void CComponentDatabase::clearComponents() 
    {
        m_componentMaps.clear();
    }

} // namespace chestnut
