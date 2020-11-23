#ifndef __CHESTNUT_WORLD_H__
#define __CHESTNUT_WORLD_H__

#include "engine/ecs/ecs.hpp"
#include "engine/event_system/event_system.hpp"

#include <forward_list>

namespace chestnut
{
    class CChestnutWorld
    {
    private:
        guid_t m_guidCounter = 0;
        std::forward_list< std::type_index > m_typesOfNewComponents;

        CComponentDatabase m_componentDB;
        std::forward_list< IComponentSystem* > m_componentSystemList;
        CEventManager m_eventManager;

    public:
        CChestnutWorld();
        ~CChestnutWorld();

        guid_t createEntity();

        template< typename T >
        T *createComponent( guid_t guid );

        template< typename T >
        T *getComponent( guid_t guid );

        bool destroyEntity( guid_t guid );

        // reaturns a read-only reference to the database
        const CComponentDatabase& getComponentDatabase() const;

        CEventManager& getEventManager();

        void update( float deltaTime );
    };

    template< typename T >
    T* CChestnutWorld::createComponent( guid_t guid ) 
    {
        if( m_componentDB.hasComponent<T>( guid ) )
            return m_componentDB.getComponentCasted<T>( guid );
        else
        {
            T *component = new T();
            component->parentGUID = guid;
            m_componentDB.pushComponent( component );
            m_typesOfNewComponents.push_front( std::type_index( typeid( T ) ) );
            return component;
        }
    }
    
    template<typename T>
    T* CChestnutWorld::getComponent( guid_t guid )
    {
        return m_componentDB.getComponentCasted<T>( guid );
    }
    
} // namespace chestnut

#endif // __CHESTNUT_WORLD_H__