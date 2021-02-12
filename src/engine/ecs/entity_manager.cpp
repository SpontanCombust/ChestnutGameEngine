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

} // namespace chestnut
