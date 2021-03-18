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

    template< typename T >
    bool CComponentDatabase::hasComponentsType() const
    {
        if( m_componentMaps.find( TINDEX(T) ) != m_componentMaps.end() )
            return true;
        return false;
    }
    
    template< typename T >
    bool CComponentDatabase::hasComponent( entityid_t id ) const
    {
        if( !hasComponentsType<T>() )
            return false;

        auto& typedCompMap = m_componentMaps.at( TINDEX(T) );
        if( typedCompMap.find( id ) != typedCompMap.end() )
            return true;
        return false;
    }
    
    template< typename T >
    T& CComponentDatabase::getComponent( entityid_t id ) const
    {
        if( !hasComponentsType<T>() )
        {
            throw ChestnutException( "No component with that type found!" );
        }

        auto& typedCompMap = m_componentMaps.at( TINDEX(T) );

        bool found = false;
        entityid_t  pair_id;
        IComponent *pair_component;
        for( auto& pair : typedCompMap )
        {
            pair_id = pair.first;
            pair_component = pair.second;

            if( pair_id == id )
            {
                found = true;
                break;
            }
        }

        if( found )
        {
            return *dynamic_cast<T*>( pair_component );
        }
        else
        {
            throw ChestnutException( "No component with that type and ID found!" );
        }
    }
    
    template< typename T >
    bool CComponentDatabase::eraseComponent( entityid_t id, bool shouldDelete ) 
    {
        if( !hasComponent<T>( id ) )
            return false;

        std::type_index tindex = TINDEX(T);
        
        if( shouldDelete )
        {
            IComponent *component = m_componentMaps[tindex][id];
            delete component;
            component = nullptr;
        }
        m_componentMaps[tindex].erase( id );

        if( m_componentMaps[tindex].empty() )
            m_componentMaps.erase( tindex );

        return true;
    }
    
    template< typename T >
    std::unordered_map< entityid_t, T* > CComponentDatabase::getComponentMapOfType() const
    {
        std::unordered_map< entityid_t, IComponent* > typedCompMap;
        std::unordered_map< entityid_t, T* > typedCastedCompMap;

        // if has no components of that type, return empty map
        if( !hasComponentsType<T>() )
        {
            return typedCastedCompMap;
        }

        typedCompMap = m_componentMaps.at( TINDEX(T) );
        for( const auto &pair : typedCompMap )
        {
            const entityid_t &id = pair.first;
            IComponent *component = pair.second;

            typedCastedCompMap[id] = dynamic_cast<T*>( component );
        }

        return typedCastedCompMap;
    }

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_DATABASE_H__