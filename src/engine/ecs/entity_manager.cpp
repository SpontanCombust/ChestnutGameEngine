#include "engine/ecs/entity_manager.hpp"

namespace chestnut
{
    CEntityManager::CEntityManager( CEventManager& eventManagerRef )
    {

    }

    CEntityManager::~CEntityManager() 
    {
        m_componentDB.clearComponents();
    }

    guid_t CEntityManager::createEntity() 
    {
        return ++m_guidCounter;
    }

    bool CEntityManager::destroyEntity( guid_t guid ) 
    {
        return m_componentDB.eraseComponents( guid, true );
    }

    void CEntityManager::destroyAllEntities() 
    {
        m_componentDB.clearComponents();
    }

    const CComponentDatabase& CEntityManager::getComponentDatabase() const
    {
        return m_componentDB;
    }

    std::list< std::type_index > CEntityManager::getTypesOfRecentComponents() const
    {
        return m_typesOfRecentComponents;
    }

    void CEntityManager::clearTypesOfRecentComponents() 
    {
        m_typesOfRecentComponents.clear();
    }

    // void CEntityManager::update( float deltaTime ) 
    // {
    //     m_eventManagerRef.update( deltaTime );

    //     for( IComponentSystem *cs : m_componentSystemList )
    //     {
    //         cs->update( deltaTime );

    //         if( !m_typesOfNewComponents.empty() )
    //         {
    //             if( cs->needsAnyOfComponents( m_typesOfNewComponents ) )
    //                 cs->fetchComponents( m_componentDB );
    //         }
    //     }
    //     m_typesOfNewComponents.clear();
    // }

} // namespace chestnut
