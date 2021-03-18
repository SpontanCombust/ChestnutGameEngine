#include "entity_manager.hpp"

namespace chestnut
{
    CEntityManager::CEntityManager()
    {

    }

    CEntityManager::~CEntityManager() 
    {
        m_componentDB.clearComponents();
    }

    entityid_t CEntityManager::createEntity() 
    {
        return ++m_entityIDCounter;
    }

    bool CEntityManager::destroyEntity( entityid_t id ) 
    {
        return m_componentDB.eraseComponents( id, true );
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

} // namespace chestnut
