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
        guid_t m_guidCounter = 0;
        std::list< std::type_index > m_typesOfRecentComponents;

        CComponentDatabase m_componentDB;

    public:
        CEntityManager();
        ~CEntityManager();

        guid_t createEntity();

        template< typename T >
        T& createComponent( guid_t guid );

        bool destroyEntity( guid_t guid );

        void destroyAllEntities();

        const CComponentDatabase& getComponentDatabase() const;

        std::list< std::type_index > getTypesOfRecentComponents() const;
        void clearTypesOfRecentComponents();
    };

    template< typename T >
    T& CEntityManager::createComponent( guid_t guid ) 
    {
        if( m_componentDB.hasComponent<T>( guid ) )
        {
            return m_componentDB.getComponent<T>( guid );
        }
        else
        {
            T *component = new T();
            component->parentGUID = guid;
            m_componentDB.pushComponent( component );
            m_typesOfRecentComponents.push_front( TINDEX(T) );
            return *component;
        }
    }

} // namespace chestnut

#endif // __CHESTNUT_ENTITY_MANAGER_H__