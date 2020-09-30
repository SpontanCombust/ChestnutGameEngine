#include "engine/ecs/ecs.hpp"

#include <algorithm>

namespace chestnut
{
    CChestnutECS::CChestnutECS() 
    {
        m_componentSystems.push_back( new CRenderingComponentSystem );
    }
    
    CChestnutECS::~CChestnutECS() 
    {
        for( IComponentSystem *cs : m_componentSystems )
        {
            delete cs;   
            cs = nullptr;
        }
        m_componentSystems.clear();
    }
    
    void CChestnutECS::onTick() 
    {
        for( IComponentSystem *cs : m_componentSystems )
        {
            cs->manageCurrentComponents();
        }
    }
    
    bool CChestnutECS::registerEntity( CEntity *entity, bool generateGUID ) 
    {
        if( isEntityRegistered( entity ) )
            return false;

        uint64_t guid;
        if( generateGUID )
        {
            guid = guidGenerator.generate();
            entity->m_GUID = guid; // assume no collisions will happend due to super large random range
        }
        else
            guid = entity->getGUID();

        m_registeredGUIDs.push_back( guid );
        
        if( !( entity->m_components.empty() ) )
        {
            IComponent *component;
            for( auto &pair : entity->m_components )
            {
                component = pair.second;
                component->parentGUID = guid;
            }
        }

        return true;
    }
    
    bool CChestnutECS::pullComponentsFromEntity( CEntity *entity ) 
    {
        if( !isEntityRegistered( entity ) )
            return false;

        if( !( entity->m_components.empty() ) )
        {
            IComponent *component;
            for( const auto& pair : entity->m_components )
            {
                component = pair.second;
                if( !m_componentDB.pushComponent( component ) )
                    return false;
            }

            std::vector< std::string > compTypes = entity->getComponentTypes();
            feedComponentSystemsIfNeeded( compTypes );
        }

        return true;
    }
    
    bool CChestnutECS::registerEntityAndPullComponents( CEntity *entity, bool generateGUID ) 
    {
        if( registerEntity( entity, generateGUID ) )
            return pullComponentsFromEntity( entity );
        else
            return false;
    }

    const CComponentDatabase& CChestnutECS::getComponentDatabase() const
    {
        return m_componentDB;
    }

    bool CChestnutECS::isEntityRegistered( CEntity *entity ) 
    {
        if( entity == nullptr )
            return false;
        else if( entity->m_GUID == GUID_UNREGISTERED )
            return false;

        return std::count( m_registeredGUIDs.begin(), m_registeredGUIDs.end(), entity->getGUID() );
    }

    void CChestnutECS::feedComponentSystemsIfNeeded( std::vector< std::string >& updatedCompTypes ) 
    {
        for( IComponentSystem *cs : m_componentSystems )
        {
            if( cs->needsComponents( updatedCompTypes ) )
                cs->fetchComponents( m_componentDB );
        }
    }

} // namespace chestnut
