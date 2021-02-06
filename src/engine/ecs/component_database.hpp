#ifndef __CHESTNUT_COMPONENT_DATABASE_H__
#define __CHESTNUT_COMPONENT_DATABASE_H__

#include "component.hpp"
#include "engine/debug/debug.hpp"

#include <unordered_map>
#include <typeindex>

namespace chestnut
{   
    class CComponentDatabase
    {
    private:
        std::unordered_map< std::type_index, std::unordered_map< guid_t, IComponent* > > m_componentMaps;

    public:
        template< typename T >
        bool hasComponentsType() const;

        template< typename T >
        bool hasComponent( guid_t guid ) const;

        bool pushComponent( IComponent *component );

        template< typename T >
        IComponent *getComponent( guid_t guid ) const;

        template< typename T >
        T *getComponentCasted( guid_t guid ) const;

        template< typename T >
        bool eraseComponent( guid_t guid, bool shouldDelete = true );

        bool eraseComponents( guid_t guid, bool shouldDelete = true );

        void clearComponents();

        template< typename T >
        std::unordered_map< guid_t, T* > getComponentMapOfType() const;
    };

    template< typename T >
    bool CComponentDatabase::hasComponentsType() const
    {
        if( m_componentMaps.find( std::type_index( typeid(T) ) ) != m_componentMaps.end() )
            return true;
        return false;
    }
    
    template< typename T >
    bool CComponentDatabase::hasComponent( guid_t guid ) const
    {
        if( !hasComponentsType<T>() )
            return false;

        auto& typedCompMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        if( typedCompMap.find( guid ) != typedCompMap.end() )
            return true;
        return false;
    }
    
    template< typename T >
    IComponent *CComponentDatabase::getComponent( guid_t guid ) const
    {
        if( !hasComponentsType<T>() )
            return nullptr;

        auto& typedCompMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        for( auto& pair : typedCompMap )
        {
            guid_t &pair_guid = pair.first;
            IComponent *pair_component = pair.second;

            if( pair_guid == guid )
                return pair_component;
        }
        return nullptr;
    }

    template< typename T >
    T *CComponentDatabase::getComponentCasted( guid_t guid ) const
    {
        if( !hasComponentsType<T>() )
            return nullptr;

        auto& compMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        guid_t pair_guid;
        IComponent *pair_component;
        for( auto& pair : compMap )
        {
            pair_guid = pair.first;
            pair_component = pair.second;

            if( pair_guid == guid )
                return dynamic_cast<T*>( pair_component );
        }
        return nullptr;
    }
    
    template< typename T >
    bool CComponentDatabase::eraseComponent( guid_t guid, bool shouldDelete ) 
    {
        if( !hasComponent<T>( guid ) )
            return false;

        std::type_index tindex = std::type_index( typeid(T) );
        
        if( shouldDelete )
        {
            IComponent *component = m_componentMaps[tindex][guid];
            delete component;
            component = nullptr;
        }
        m_componentMaps[tindex].erase( guid );

        if( m_componentMaps[tindex].empty() )
            m_componentMaps.erase( tindex );

        return true;
    }
    
    template< typename T >
    std::unordered_map< guid_t, T* > CComponentDatabase::getComponentMapOfType() const
    {
        std::unordered_map< guid_t, IComponent* > typedCompMap;
        std::unordered_map< guid_t, T* > typedCastedCompMap;

        // if has no components of that type, return empty map
        if( !hasComponentsType<T>() )
        {
            return typedCastedCompMap;
        }

        typedCompMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        for( const auto &pair : typedCompMap )
        {
            const guid_t &guid = pair.first;
            IComponent *component = pair.second;

            typedCastedCompMap[guid] = dynamic_cast<T*>( component );
        }

        return typedCastedCompMap;
    }

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_DATABASE_H__