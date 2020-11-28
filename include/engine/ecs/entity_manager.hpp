#ifndef __CHESTNUT_ENTITY_MANAGER_H__
#define __CHESTNUT_ENTITY_MANAGER_H__

#include "ecs_utils.hpp"
#include "component.hpp"
#include "components/components.hpp"
#include "component_system.hpp"
#include "component_systems/component_systems.hpp"
#include "engine/event_system/event_system.hpp"

#include <algorithm>
#include <list>

namespace chestnut
{
    class CEntityManager
    {
    private:
        guid_t m_guidCounter = 0;
        std::forward_list< std::type_index > m_typesOfNewComponents;

        CComponentDatabase m_componentDB;
        std::list< IComponentSystem* > m_componentSystemList;

        CEventManager& m_eventManagerRef;

    public:
        CEntityManager( CEventManager& eventManagerRef );
        ~CEntityManager();

        guid_t createEntity();

        template< typename T >
        T *createComponent( guid_t guid );

        template< typename T >
        T *getComponent( guid_t guid );

        bool destroyEntity( guid_t guid );

        /* creates new components system and puts it in the list according to the priority
           the lower the priority, the later the system will be called on every tick
           if there already exists a component system with given priority, the new system is put after the last existing one with the same priority
           exceptions:  when given HIGHEST priority the system is always put at the beginning of the list
                        when given LOWEST priority the system is always put at the end of the list
        */
        template< class T >
        void createComponentSystem( unsigned int priority = ComponentSystemPriority::DEFAULT );

        void createNativeComponentSystems();

        // reaturns a read-only reference to the database
        const CComponentDatabase& getComponentDatabase() const;

        void update( float deltaTime );

    private:
        std::list< IComponentSystem* >::iterator findSpotForComponentSystem( unsigned int priority );
    };

    template< typename T >
    T* CEntityManager::createComponent( guid_t guid ) 
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
    
    template< typename T >
    T* CEntityManager::getComponent( guid_t guid )
    {
        return m_componentDB.getComponentCasted<T>( guid );
    }
    
    template< class T >
    void CEntityManager::createComponentSystem( unsigned int priority ) 
    {
        if( std::any_of( m_componentSystemList.begin(), m_componentSystemList.end(),
                []( IComponentSystem *componentSystem )
                {
                    return std::type_index( typeid( *componentSystem ) ) == std::type_index( typeid( T ) );
                }
            )
        )
        {
            LOG_CHANNEL( "CEntityManager", "Component system already exists!" );
            return;
        }

        IComponentSystem *componentSystem = new T();
        componentSystem->setPriority( priority );
        m_componentSystemList.insert( findSpotForComponentSystem( priority ), componentSystem );
    }

} // namespace chestnut

#endif // __CHESTNUT_ENTITY_MANAGER_H__