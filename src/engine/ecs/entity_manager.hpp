#ifndef __CHESTNUT_ENTITY_MANAGER_H__
#define __CHESTNUT_ENTITY_MANAGER_H__

#include "components/components.hpp"
#include "component_database.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

#include <algorithm>
#include <list>

namespace chestnut
{
    class CEntityManager
    {
    private:
        entityid_t m_entityIDCounter = 0;
        std::list< std::type_index > m_typesOfRecentComponents;

        CComponentDatabase m_componentDB;

    public:
        CEntityManager();
        ~CEntityManager();

        entityid_t createEntity();

        template< typename T >
        T& createComponent( entityid_t id );

        bool destroyEntity( entityid_t id );

        void destroyAllEntities();

        const CComponentDatabase& getComponentDatabase() const;

        std::list< std::type_index > getTypesOfRecentComponents() const;
        void clearTypesOfRecentComponents();
    };

} // namespace chestnut


#include "entity_manager.tpp"


#endif // __CHESTNUT_ENTITY_MANAGER_H__