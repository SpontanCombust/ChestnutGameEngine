#include "engine/misc/exception.hpp"

namespace chestnut
{
    // ========================= PUBLIC ========================= //

    template< typename T >
    CEntityManager& CEntityManager::prepareForComponentType() 
    {
        componenttindex_t tindex = TINDEX(T);

        auto it = m_mapComponentVecWrappers.find( tindex );
        // if vector wrapper doesn't yet exist for this type, create it
        if( it == m_mapComponentVecWrappers.end() )
        {
            m_mapComponentVecWrappers[ tindex ] = new CComponentVectorWrapper<T>();
        }

        return *this;
    }



    template< typename T >
    T* CEntityManager::createComponent( entityid_t id ) 
    {
        prepareForComponentType<T>();

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
    T* CEntityManager::getComponent( entityid_t id ) 
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
