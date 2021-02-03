#ifndef __CHESTNUT_ENTITY_H__
#define __CHESTNUT_ENTITY_H__

#include "component.hpp"

#include <vector>
#include <unordered_map>
#include <typeindex>

namespace chestnut
{    
    class CEntity
    {
    private:
        friend class CChestnutECS;

    protected:
        guid_t m_GUID;
        std::unordered_map< std::type_index, IComponent* > m_components;

    public:
        CEntity() : m_GUID( GUID_UNREGISTERED ) {}

        guid_t getGUID() const;

        bool addComponent( IComponent *component );

        template< typename T >
        bool hasComponent() const;

        template< typename T >
        IComponent *getComponent();

        const std::vector< std::type_index > getComponentTypeIndexes() const;
    };

    template< typename T >
    bool CEntity::hasComponent() const
    {
        std::type_index tindex = std::type_index( typeid(T) );
        return ( m_components.find( tindex ) != m_components.end() );    
    }
    
    template<typename T>
    IComponent* CEntity::getComponent() 
    {
        std::type_index tindex = std::type_index( typeid(T) );
        if( hasComponent<T>() )
            return m_components[tindex];
        else
            return nullptr;
    }
    

} // namespace chestnut 

#endif // __CHESTNUT_ENTITY_H__
