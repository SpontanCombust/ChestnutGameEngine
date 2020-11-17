#include "engine/app/world.hpp"

namespace chestnut
{
    CChestnutWorld::CChestnutWorld() 
    {
        m_componentSystemList.push_front( new CRenderingComponentSystem() );
    }

    CChestnutWorld::~CChestnutWorld() 
    {
        m_componentDB.clearComponents();

        for( IComponentSystem *cs : m_componentSystemList )
        {
            delete cs;   
            cs = nullptr;
        }
        m_componentSystemList.clear();

        m_eventManager.clearListeners();
    }

    guid_t CChestnutWorld::createEntity() 
    {
        //TODO will need some better system for this
        return ++m_guidCounter;
    }

    bool CChestnutWorld::destroyEntity( guid_t guid ) 
    {
        return m_componentDB.eraseComponents( guid, true );
    }

    const CComponentDatabase& CChestnutWorld::getComponentDatabase() const
    {
        return m_componentDB;
    }

    CEventManager& CChestnutWorld::getEventManager() 
    {
        return m_eventManager;
    }

    void CChestnutWorld::update( float deltaTime ) 
    {
        m_eventManager.update( deltaTime );

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
