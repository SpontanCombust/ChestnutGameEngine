#include "entity_manager.hpp"

namespace chestnut
{   
    // ========================= PUBLIC ========================= //

    CEntityManager::CEntityManager() 
    {
        m_idCounter = 0;
    }

    CEntityManager::~CEntityManager() 
    {
        destroyAllEntities();

        for( auto& [ tindex, wrapper ] : m_mapComponentVecWrappers )
        {
            delete wrapper;
            wrapper = nullptr;
        }

        m_mapComponentVecWrappers.clear();
    }



    entityid_t CEntityManager::createEntity() 
    {
        ++m_idCounter;
        m_entityRegistry.addEntity( m_idCounter );
        return m_idCounter;
    }

    std::vector< entityid_t > CEntityManager::createEntities( int amount ) 
    {
        std::vector< entityid_t > ids;

        for (int i = 0; i < amount; i++)
        {
            ++m_idCounter;
            m_entityRegistry.addEntity( m_idCounter );
            ids.push_back( m_idCounter );
        }
        
        return ids;
    }

    bool CEntityManager::hasEntity( entityid_t id ) const
    {
        return m_entityRegistry.hasEntity( id );
    }

    void CEntityManager::destroyEntity( entityid_t id ) 
    {
        if( !hasEntity( id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Couldn't destroy entity " << id << "! It doesn't exist!" );
            return;
        }

        SComponentSetSignature signature;
        CComponentBatch *batch;
        IComponentVectorWrapper *vecWrapper;

        signature = m_entityRegistry.getEntitySignature( id ); // hasEntity() ensures entity exists
        batch = getBatchWithSignature( signature );

        // remove references to entity's components stored in the batch
        if( batch )
        {
            batch->removeComponentSet( id );

            if( batch->getEntityCount() == 0 )
            {
                destroyBatchWithSignature( signature );
            }
        }

        // remove actual components belonging to entity
        for( const std::type_index& tindex : signature.componentTindexes )
        {
            vecWrapper = getComponentVectorWrapper( tindex );
            vecWrapper->erase( id );
        }

        // remove entity from registry
        m_entityRegistry.removeEntity( id );
    }

    void CEntityManager::destroyEntities( std::vector< entityid_t > ids ) 
    {
        for( const entityid_t& id : ids )
        {
            destroyEntity( id );
        }
    }

    void CEntityManager::destroyAllEntities() 
    {
        for( auto& [ tindex, wrapper ] : m_mapComponentVecWrappers )
        {
            wrapper->clear();
        }

        m_vecCompBatches.clear();

        m_entityRegistry.removeAllEntities();
    }



    IComponent* CEntityManager::createComponent( componenttindex_t compTindex, entityid_t id ) 
    {
        if( !isPreparedForComponentType( compTindex ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity manager hasn't yet been prepared for this component type: " << compTindex.name() << " !" );
            return nullptr;
        }
        if( !hasEntity( id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " doesn't exist!" );
            return nullptr;
        }
        if( hasComponent( compTindex, id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " already has component " << compTindex.name() );
            return getComponent( compTindex, id );
        }

        IComponentVectorWrapper *wrapper;
        IComponent *uncastedComp;
        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;


        // compute signatures //
        oldSignature = m_entityRegistry.getEntitySignature( id ); // hasEntity() assures entity exists
        newSignature = oldSignature;
        newSignature.add( compTindex );


        // create an instance of the component //
        wrapper = getComponentVectorWrapper( compTindex ); // isPreparedForComponentType() assures wrapper exists
        uncastedComp = wrapper->push_back( id );


        // update component batches //
        if( !moveEntityAccrossBatches( id, oldSignature, newSignature ) )
        {
            wrapper->erase( id );
            return nullptr;
        }


        // update entity registry - apply new signature to entity //
        m_entityRegistry.updateEntity( id, newSignature );


        return uncastedComp;
    }

    bool CEntityManager::hasComponent( componenttindex_t compTindex, entityid_t id ) const
    {
        if( !hasEntity( id ) )
        {
            return false;
        }
        if( !isPreparedForComponentType( compTindex ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity manager hasn't yet been prepared for this component type: " << compTindex.name() << " !" );
            return false;
        }
        
        SComponentSetSignature signature;

        signature = m_entityRegistry.getEntitySignature( id ); // hasEntity() assures entity exists
        return signature.includes( compTindex );
    }

    IComponent* CEntityManager::getComponent( componenttindex_t compTindex, entityid_t id ) 
    {
        if( !hasComponent( compTindex, id ) )
        {
            return nullptr;
        }

        IComponentVectorWrapper *wrapper;
        IComponent *uncastedComp;

        wrapper = m_mapComponentVecWrappers[ compTindex ]; // hasComponent() assures wrapper exists 
        uncastedComp = wrapper->find( id );

        return uncastedComp;
    }

    void CEntityManager::destroyComponent( componenttindex_t compTindex, entityid_t id ) 
    {
        if( !hasComponent( compTindex, id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " doesn't have component " << compTindex.name() );
            return;
        }

        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;
        IComponentVectorWrapper *wrapper;

        // compute signatures //
        oldSignature = m_entityRegistry.getEntitySignature( id ); // hasComponent() assures entity exists
        newSignature = oldSignature;
        newSignature.remove( compTindex );


        // update component batches //
        if( !moveEntityAccrossBatches( id, oldSignature, newSignature ) )
        {
            return;
        }


        // erase instance of the destroyed component //
        wrapper = getComponentVectorWrapper( compTindex ); // hasComponent() assures wrapper exists
        wrapper->erase( id );


        // update registry //
        m_entityRegistry.updateEntity( id, newSignature );
    }



    entityid_t CEntityManager::createEntity( SComponentSetSignature signature ) 
    {
        // validation stage
        for( const componenttindex_t& compTindex : signature.componentTindexes )
        {
            if( !isPreparedForComponentType( compTindex ) )
            {
                LOG_CHANNEL( "ENTITY_MANAGER", "Entity manager hasn't yet been prepared for this component type: " << compTindex.name() << " !" );
                return ENTITY_ID_INVALID;
            }
        }

        // creation stage
        entityid_t id;
        IComponentVectorWrapper *wrapper;
        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;

        oldSignature = SComponentSetSignature(); // empty signature
        newSignature = signature;

        id = ++m_idCounter;
        m_entityRegistry.addEntity( id, newSignature );

        for( const componenttindex_t& compTindex : signature.componentTindexes )
        {
            // create an instance of the component //
            wrapper = getComponentVectorWrapper( compTindex ); // validation stage with isPreparedForComponentType() assures wrapper exists
            wrapper->push_back( id );
        }

        // update component batches //
        if( !moveEntityAccrossBatches( id, oldSignature, newSignature ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Error occured while processing batch for entity with signature: " << newSignature.toString() << " ! Halting entity creation!" );
            destroyEntity( id );
            return ENTITY_ID_INVALID;
        }

        return id;
    }

    std::vector< entityid_t > CEntityManager::createEntities( SComponentSetSignature signature, int amount ) 
    {
        std::vector< entityid_t > ids;

        // validation stage
        if( amount <= 0 )
        {
            return ids;
        }

        for( const componenttindex_t& compTindex : signature.componentTindexes )
        {
            if( !isPreparedForComponentType( compTindex ) )
            {
                LOG_CHANNEL( "ENTITY_MANAGER", "Entity manager hasn't yet been prepared for this component type: " << compTindex.name() << " !" );
                return ids; // returns empty vector
            }
        }

        // creation stage
        entityid_t id;
        IComponentVectorWrapper *wrapper;
        SComponentSetSignature oldSignature;
        SComponentSetSignature newSignature;

        oldSignature = SComponentSetSignature(); // empty signature
        newSignature = signature;

        for (int i = 0; i < amount; i++)
        {
            id = ++m_idCounter;
            m_entityRegistry.addEntity( id, signature );

            for( const componenttindex_t& compTindex : signature.componentTindexes )
            {
                // create an instance of the component //
                wrapper = getComponentVectorWrapper( compTindex ); // validation stage with isPreparedForComponentType() assures wrapper exists
                wrapper->push_back( id );
            }

            // update component batches //
            if( !moveEntityAccrossBatches( id, oldSignature, newSignature ) )
            {
                LOG_CHANNEL( "ENTITY_MANAGER", "Error occured while processing batch for entity with signature: " << signature.toString() << " ! Halting entity creation!" );
                destroyEntity( id );
                break;
            }

            ids.push_back( id );
        }

        return ids;
    }



    std::vector< CComponentBatch * > CEntityManager::getComponentBatches() 
    {
        std::vector< CComponentBatch * > vec;

        for( CComponentBatch& batch : m_vecCompBatches )
        {
            vec.push_back( &batch );
        }

        return vec;
    }



    // ========================= PRIVATE ========================= //

    bool CEntityManager::isPreparedForComponentType( componenttindex_t compTindex ) const
    {
        auto it = m_mapComponentVecWrappers.find( compTindex );
        // if vector wrapper doesn't yet exist for this type
        if( it != m_mapComponentVecWrappers.end() )
        {
            return true;
        }
        
        return false;
    }



    IComponentVectorWrapper* CEntityManager::getComponentVectorWrapper( componenttindex_t compTypeTindex ) const
    {
        IComponentVectorWrapper *wrapper;

        wrapper = nullptr;

        auto it = m_mapComponentVecWrappers.find( compTypeTindex );
        // vector wrapper doesn't yet exist for this type
        if( it != m_mapComponentVecWrappers.end() )
        {
            wrapper = m_mapComponentVecWrappers.at( compTypeTindex );
        }

        return wrapper;
    }



    bool CEntityManager::existsBatchWithSignature( SComponentSetSignature signature ) const
    {
        // we don't make batches for empty signatures
        if( signature.isEmpty() )
        {
            return false;
        }

        for( const CComponentBatch& batch : m_vecCompBatches )
        {
            if( batch.getSignature() == signature )
            {
                return true;
            }
        }

        return false;
    }

    CComponentBatch *CEntityManager::getBatchWithSignature( SComponentSetSignature signature ) 
    {
        // we don't make batches for empty signatures
        if( signature.isEmpty() )
        {
            return nullptr;
        }

        for( CComponentBatch& batch : m_vecCompBatches )
        {
            if( batch.getSignature() == signature )
            {
                return &batch;
            }
        }

        return nullptr;
    }

    void CEntityManager::createBatchWithSignature( SComponentSetSignature signature ) 
    {
        CComponentBatch batch;
        batch.setSignature( signature );
        m_vecCompBatches.push_back( batch );
    }

    void CEntityManager::destroyBatchWithSignature( SComponentSetSignature signature ) 
    {
        for( auto it = m_vecCompBatches.begin(); it != m_vecCompBatches.end(); ++it )
        {
            if( it->getSignature() == signature )
            {
                m_vecCompBatches.erase( it );
                break;
            }
        }
    }



    SComponentSet CEntityManager::buildComponentSetForEntity( entityid_t id, SComponentSetSignature signature ) 
    {
        SComponentSet compSet;
        IComponentVectorWrapper *wrapper;
        IComponent *comp;

        compSet.componentOwnerID = id;

        for( const std::type_index& tindex : signature.componentTindexes )
        {
            wrapper = getComponentVectorWrapper( tindex );

            if( wrapper )
            {
                comp = wrapper->find( id );

                if( comp )
                {
                    compSet.addComponent( comp );
                }
            }
        }

        return compSet;
    }

    bool CEntityManager::moveEntityAccrossBatches( entityid_t id, SComponentSetSignature oldSignature, SComponentSetSignature newSignature ) 
    {
        CComponentBatch *oldBatch;
        CComponentBatch *newBatch;
        SComponentSet compSet;

        // check if entity had components before
        // if it didn't, don't bother trying to remove it from any batch
        if( !oldSignature.isEmpty() )
        {
            oldBatch = getBatchWithSignature( oldSignature );
            if( oldBatch )
            {
                oldBatch->removeComponentSet( id );

                if( oldBatch->getEntityCount() == 0 )
                {
                    destroyBatchWithSignature( oldSignature );
                }
            }
        }

        // check if entity will have any components left
        // if it won't, there won't be any components to be assigned to a batch
        if( !newSignature.isEmpty() )
        {
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
                return false;
            }
        }

        return true;
    }

} // namespace chestnut
