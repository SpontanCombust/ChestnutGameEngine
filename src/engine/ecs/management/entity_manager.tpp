#include "engine/misc/exception.hpp"

namespace chestnut
{
    template<typename T>
    IComponentVectorWrapper *CEntityManager::getComponentVectorWrapper() 
    {
        std::type_index tindex = TINDEX(T);
        IComponentVectorWrapper *wrapper;

        auto it = m_mapComponentVecWrappers.find( tindex );
        // if vector wrapper doesn't yet exist for this type
        if( it == m_mapComponentVecWrappers.end() )
        {
            m_mapComponentVecWrappers[ tindex ] = new CComponentVectorWrapper<T>();
        }

        wrapper = m_mapComponentVecWrappers[ tindex ];

        return wrapper;
    }



    template<typename T>
    T* CEntityManager::createComponent( entityid_t id ) 
    {
        if( hasComponent<T>( id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " already has component " << TINDEX_NAME(T) );
            return getComponent<T>( id );
        }

        IComponentVectorWrapper *wrapper;
        IComponent *uncastedComp;
        T *castedComp;
        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;
        CComponentBatch *oldBatch;
        CComponentBatch *newBatch;
        SComponentSet compSet;

        try
        {
            // compute signatures //
            oldSignature = m_entityRegistry.getEntitySignature( id );
            newSignature = oldSignature;
            newSignature.add<T>();


            // create an instance of the component //
            wrapper = getComponentVectorWrapper<T>();
            uncastedComp = wrapper->push_back( id );
            castedComp = dynamic_cast<T*>( uncastedComp );

            if( !castedComp )
            {
                LOG_CHANNEL( "ENTITY_MANAGER", "Error occured while creating new component!" );
                wrapper->erase( id );
                return nullptr;
            }


            // update component batches //
            // move entity's components from previous batch to current one //
            if( !oldSignature.isEmpty() )
            {
                oldBatch = getBatchWithSignature( oldSignature );
                oldBatch->removeComponentSet( id );

                if( oldBatch->getEntityCount() == 0 )
                {
                    destroyBatchWithSignature( oldSignature );
                }
            }
            
            if( !existsBatchWithSignature( newSignature ) )
            {
                createBatchWithSignature( newSignature );
            }

            // get batch with the same signature as entity
            newBatch = getBatchWithSignature( newSignature );
            // get set of current components belonging to entity
            compSet = buildComponentSetForEntity( id, newSignature );

            if( !newBatch->submitComponentSet( compSet ) )
            {
                LOG_CHANNEL( "ENTITY_MANAGER", "Error occured while adding components to new batch." );
                wrapper->erase( id );
                return nullptr;
            }


            // update entity registry - apply new signature to entity //
            m_entityRegistry.updateEntity( id, newSignature );


            return castedComp;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return nullptr;
        }
    }

    template<typename T>
    bool CEntityManager::hasComponent( entityid_t id ) const
    {
        if( !hasEntity( id ) )
        {
            return false;
        }

        SComponentSetSignature signature;

        try
        {
            signature = m_entityRegistry.getEntitySignature( id );
            return signature.includes<T>();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
    }

    template<typename T>
    T* CEntityManager::getComponent( entityid_t id ) 
    {
        if( !hasComponent<T>( id ) )
        {
            return nullptr;
        }

        IComponentVectorWrapper *wrapper;
        IComponent *uncastedComp;
        T *castedComp;

        wrapper = m_mapComponentVecWrappers[ TINDEX(T) ];
        uncastedComp = wrapper->at( id );
        castedComp = dynamic_cast<T*>( uncastedComp );

        if( !castedComp )
        {
            throw ChestnutException( "Component cast was unsuccessful!" );
        }
        else
        {
            return castedComp;
        }
    }

    template<typename T>
    void CEntityManager::destroyComponent( entityid_t id ) 
    {
        if( !hasComponent<T>( id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " doesn't have component " << TINDEX_NAME(T) );
            return;
        }

        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;
        CComponentBatch *oldBatch;
        CComponentBatch *newBatch;
        SComponentSet compSet;
        IComponentVectorWrapper *wrapper;

        try
        {
            // compute signatures //
            oldSignature = m_entityRegistry.getEntitySignature( id );
            newSignature = oldSignature;
            newSignature.remove<T>();


            // update component batches //
            oldBatch = getBatchWithSignature( oldSignature );
            oldBatch->removeComponentSet( id );

            if( oldBatch->getEntityCount() == 0 )
            {
                destroyBatchWithSignature( oldSignature );
            }

            if( !newSignature.isEmpty() )
            {
                if( !existsBatchWithSignature( newSignature ) )
                {
                    createBatchWithSignature( newSignature );
                }

                newBatch = getBatchWithSignature( newSignature );
                compSet = buildComponentSetForEntity( id, newSignature );

                if( !newBatch->submitComponentSet( compSet ) )
                {
                    LOG_CHANNEL( "ENTITY_MANAGER", "Error occured while adding components to new batch." );
                    return;
                }
            }


            // erase instance of the destroyed component //
            wrapper = getComponentVectorWrapper<T>();
            wrapper->erase( id );


            // update registry //
            m_entityRegistry.updateEntity( id, newSignature );
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
                
    }

} // namespace chestnut
