#include "engine/ecs/entity.hpp"

#include "engine/debug/debug.hpp"

namespace chestnut
{
    void CEntity::setGUID( uint64_t guid )
    {
        m_GUID = guid;
    }

    uint64_t CEntity::getGUID() const
    {
        return m_GUID;
    }

    bool CEntity::addComponent( SComponent *component ) 
    {
        if( component == nullptr )
            return false;

        std::string compType = component->getTypeString();
        if( m_components.find(compType) != m_components.end() )
        {
            LOG( "Entity " + to_string(m_GUID) + " already has component: " + compType );
            return false;
        }
        
        m_components[compType] = component;
        return true;
    }

    bool CEntity::hasComponent( const std::string componentType ) const
    {
        return ( m_components.find( componentType ) != m_components.end() );
    }
    
    SComponent* CEntity::getComponent( const std::string componentType ) 
    {
        if( hasComponent( componentType ) )
            return m_components[componentType];
        else
            return nullptr;    
    }

} // namespace chestnut 