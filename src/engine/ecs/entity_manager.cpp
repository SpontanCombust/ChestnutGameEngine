#include "engine/ecs/entity_manager.hpp"

namespace chestnut
{
    CEntityManager::CEntityManager( CEventManager& eventManagerRef )
    : m_eventManagerRef( eventManagerRef )
    {
        m_componentSystemList.push_front( new CRenderingComponentSystem() );
    }

    CEntityManager::~CEntityManager() 
    {
        m_componentDB.clearComponents();

        for( IComponentSystem *cs : m_componentSystemList )
        {
            delete cs;   
            cs = nullptr;
        }
        m_componentSystemList.clear();

        m_eventManagerRef.clearListeners();
    }

    guid_t CEntityManager::createEntity() 
    {
        //TODO will need some better system for this
        return ++m_guidCounter;
    }

    bool CEntityManager::destroyEntity( guid_t guid ) 
    {
        return m_componentDB.eraseComponents( guid, true );
    }

    const CComponentDatabase& CEntityManager::getComponentDatabase() const
    {
        return m_componentDB;
    }

    void CEntityManager::update( float deltaTime ) 
    {
        m_eventManagerRef.update( deltaTime );

        for( IComponentSystem *cs : m_componentSystemList )
        {
            cs->update( deltaTime );

            if( !m_typesOfNewComponents.empty() )
            {
                if( cs->needsAnyOfComponents( m_typesOfNewComponents ) )
                    cs->fetchComponents( m_componentDB );
            }
        }
        m_typesOfNewComponents.clear();
    }

} // namespace chestnut
