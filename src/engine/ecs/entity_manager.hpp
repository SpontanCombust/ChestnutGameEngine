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

    template< typename T >
    T& CEntityManager::createComponent( entityid_t id ) 
    {
        if( m_componentDB.hasComponent<T>( id ) )
        {
            return m_componentDB.getComponent<T>( id );
        }
        else
        {
            T *component = new T();
            component->ownerID = id;
            m_componentDB.pushComponent( component );
            m_typesOfRecentComponents.push_front( TINDEX(T) );
            return *component;
        }
    }

} // namespace chestnut

#endif // __CHESTNUT_ENTITY_MANAGER_H__