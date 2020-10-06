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
        bool hasComponentType() const;

        template< typename T >
        bool hasComponent( guid_t guid ) const;

        template< typename T >
        bool pushComponent( T *component );

        template< typename T >
        IComponent *getComponent( guid_t guid );

        template< typename T >
        IComponent *pullComponent( guid_t guid );

        template< typename T >
        void eraseComponent( guid_t guid );

        void clearComponents();

        template< typename T >
        bool fillComponentMapOfType( std::unordered_map< guid_t, T* >& compMapRef ) const;
    };

    template< typename T >
    bool CComponentDatabase::hasComponentType() const
    {
        if( m_componentMaps.find( std::type_index( typeid(T) ) ) != m_componentMaps.end() )
            return true;
        return false;   
    }
    
    template< typename T >
    bool CComponentDatabase::hasComponent( guid_t guid ) const
    {
        if( !hasComponentType<T>() )
            return false;

        auto& compMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        if( compMap.find( guid ) != compMap.end() )
            return true;
        return false;
    }
    
    template< typename T >
    bool CComponentDatabase::pushComponent( T *component ) 
    {
        if( component == nullptr )
            return false;
            
        if( IComponent *typedComp = dynamic_cast<IComponent*>( component ) )
        {
            std::type_index tindex = std::type_index( typeid( *typedComp ) );
            guid_t guid = typedComp->parentGUID;

            if( guid == GUID_UNREGISTERED )
                return false;
            else if( hasComponent<T>( guid ) )
                return false;

            m_componentMaps[tindex][guid] = typedComp;
        }
        else
        {
            LOG( "Component typecasting failed!" );
            return false;
        }
        
        return true;
    }
    
    template< typename T >
    IComponent* CComponentDatabase::getComponent( guid_t guid ) 
    {
        if( !hasComponent<T>( guid ) )
            return nullptr;

        IComponent* component = m_componentMaps[std::type_index( typeid(T) )][guid];
        
        return component;
    }
    
    template< typename T >
    IComponent* CComponentDatabase::pullComponent( guid_t guid ) 
    {
        if( !hasComponent<T>( guid ) )
            return nullptr;

        std::type_index tindex = std::type_index( typeid(T) );
        IComponent* component = m_componentMaps[tindex][guid];
        m_componentMaps[tindex].erase( guid );

        return component;
    }
    
    template< typename T >
    void CComponentDatabase::eraseComponent( guid_t guid ) 
    {
        if( !hasComponent<T>( guid ) )
            return;

        std::type_index tindex = std::type_index( typeid(T) );
        m_componentMaps[tindex].erase( guid );

        if( m_componentMaps[tindex].empty() )
            m_componentMaps.erase( tindex );
    }
    
    template< typename T >
    bool CComponentDatabase::fillComponentMapOfType( std::unordered_map< guid_t, T* >& compMapRef ) const
    {
        if( !hasComponentType<T>() )
            return false;

        auto compMap = m_componentMaps.at( std::type_index( typeid(T) ) );
        guid_t guid;
        IComponent *component;

        for( const auto &pair : compMap )
        {
            guid = pair.first;
            component = pair.second;

            if( T *derivedComp = dynamic_cast<T*>( component ) )
                compMapRef[guid] = derivedComp;
            else
            {
                LOG( "Provided typename and component type string are incompatible!" );
                return false;
            }
        }

        return true;
    }

} // namespace chestnut

#endif // __CHESTNUT_COMPONENT_DATABASE_H__