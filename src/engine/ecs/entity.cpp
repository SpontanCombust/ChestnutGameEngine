#include "engine/ecs/entity.hpp"

#include "engine/debug/debug.hpp"

namespace engine { namespace ecs {

    void CEntity::setID( uint32_t id )
    {
        m_id = id;
    }

    uint32_t CEntity::getID() const
    {
        return m_id;
    }

    bool CEntity::addComponent( CComponent *component ) 
    {
        if( component == nullptr )
            return false;

        std::string compType = component->getType();
        if( m_components.find(compType) != m_components.end() )
        {
            LOG( "Entity " + to_string(m_id) + " already has component: " + compType );
            return false;
        }
        
        m_components[compType] = component;
        return true;
    }

    bool CEntity::removeComponent( const std::string componentType ) 
    {
        int retcode;
        retcode = m_components.erase( componentType );

        if( retcode < 1 )
        {
            LOG( "No components of type " + componentType + " to be removed from entity " + to_string(m_id) );
            return false;
        }
        return true;
    }
    
    void CEntity::removeAllComponents() 
    {
        m_components.clear();
    }
    
    bool CEntity::hasComponent( const std::string componentType ) const
    {
        return ( m_components.find( componentType ) != m_components.end() );
    }
    
    CComponent* CEntity::getComponent( const std::string componentType ) 
    {
        if( hasComponent( componentType ) )
            return m_components[componentType];
        else
            return nullptr;    
    }

} /*namespace ecs*/ } // namespace engine 