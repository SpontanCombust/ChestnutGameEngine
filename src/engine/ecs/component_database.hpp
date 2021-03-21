#ifndef __CHESTNUT_COMPONENT_DATABASE_H__
#define __CHESTNUT_COMPONENT_DATABASE_H__

#include "component.hpp"
#include "engine/debug/debug.hpp"
#include "engine/misc/exception.hpp"
#include "engine/misc/tindex.hpp"
#include "engine/types.hpp"

#include <unordered_map>
#include <typeindex>

namespace chestnut
{   
    class CComponentDatabase
    {
    private:
        std::unordered_map< std::type_index, std::unordered_map< entityid_t, IComponent* > > m_componentMaps;

    public:
        template< typename T >
        bool hasComponentsType() const;

        template< typename T >
        bool hasComponent( entityid_t id ) const;

        // Throws an exception if the component is invalid 
        void pushComponent( IComponent *component );

        // Throws an exception if doesn't find the component
        template< typename T >
        T& getComponent( entityid_t id ) const;

        template< typename T >
        bool eraseComponent( entityid_t id, bool shouldDelete = true );

        bool eraseComponents( entityid_t id, bool shouldDelete = true );

        void clearComponents();

        template< typename T >
        std::unordered_map< entityid_t, T* > getComponentMapOfType() const;
    };
    
} // namespace chestnut


#include "component_database.tpp"


#endif // __CHESTNUT_COMPONENT_DATABASE_H__