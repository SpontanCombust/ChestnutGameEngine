#include "engine/misc/exception.hpp"

namespace chestnut
{
    // ========================= PUBLIC ========================= //

    template< typename T >
    void CEntityManager::setupComponentType( size_t segmentSize ) 
    {
        componenttindex_t tindex = TINDEX(T);

        auto it = m_mapCompTypeToStorage.find( tindex );
        // if storage doesn't yet exist for this type, create it
        if( it == m_mapCompTypeToStorage.end() )
        {
            m_mapCompTypeToStorage[ tindex ] = new CComponentStorage<T>( segmentSize );
        }
    }



    template< typename T >
    T* CEntityManager::createComponent( entityid_t id ) 
    {
        IComponent *uncastedComp;
        T *castedComp;

        uncastedComp = createComponent( TINDEX(T), id );
        castedComp = dynamic_cast<T*>( uncastedComp );

        return castedComp;
    }

    template< typename T >
    bool CEntityManager::hasComponent( entityid_t id ) const
    {
        return hasComponent( TINDEX(T), id );
    }

    template< typename T >
    T* CEntityManager::getComponent( entityid_t id ) const
    {
        IComponent *uncastedComp;
        T *castedComp;

        uncastedComp = getComponent( TINDEX(T), id );
        castedComp = dynamic_cast<T*>( uncastedComp );

        return castedComp;
    }

    template< typename T >
    void CEntityManager::destroyComponent( entityid_t id ) 
    {
        destroyComponent( TINDEX(T), id );
    }

} // namespace chestnut
