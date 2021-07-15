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

        for( auto& [ tindex, storage ] : m_mapCompTypeToStorage )
        {
            delete storage;
            storage = nullptr;
        }

        m_mapCompTypeToStorage.clear();
    }



    entityid_t CEntityManager::createEntity() 
    {
        ++m_idCounter;
        m_entityRegistry.addEntity( m_idCounter );
        // there are no components yet, so entity request in not needed
        return m_idCounter;
    }

    std::vector< entityid_t > CEntityManager::createEntities( unsigned int amount ) 
    {
        std::vector< entityid_t > ids;

        for (unsigned int i = 0; i < amount; i++)
        {
            ++m_idCounter;
            m_entityRegistry.addEntity( m_idCounter );
            ids.push_back( m_idCounter );
        }
        // there are no components yet, so entity requests are not needed
        return ids;
    }

    entityid_t CEntityManager::createEntity( CEntitySignature signature ) 
    {
        // creation stage
        entityid_t id;
        IComponentStorage *storage;
        SEntityRequest request;


        id = ++m_idCounter;
        m_entityRegistry.addEntity( id, signature );


        for( const componenttindex_t& compTindex : signature.m_setComponentTindexes )
        {
            // create an instance of the component //
            storage = getComponentStorage( compTindex ); // let the exception propagate if happens
            storage->createComponent( id );
        }


        // request post tick handling of batches //
        request.id = id;
        request.type = EEntityRequestType::CREATE_ENTITY;
        // old signature is not needed, because hasn't had components before
        request.newSignature = signature;

        m_queuePostTickRequests.push( request );

        // actual entity and its components are created outright to allow component initialization on user's side
        // batches are processed only through request to maintain their coherence on per tick basis
        // so that no system misses out on all new components that get created on a single tick being available at the same time

        return id;
    }

    std::vector< entityid_t > CEntityManager::createEntities( CEntitySignature signature, unsigned int amount ) 
    {
        std::vector< entityid_t > ids;

        // validation stage
        if( signature.isEmpty() )
        {
            return ids;
        }

        // creation stage

        // get all needed component vectors
        std::vector< IComponentStorage * > vecStorages;
        for( const componenttindex_t& compTindex : signature.m_setComponentTindexes )
        {
            IComponentStorage *storage;
            storage = getComponentStorage( compTindex ); // let the exception propagate if happens
            storage->reserveMoreComponents( amount );
            vecStorages.push_back( storage ); 
        }

        entityid_t id;
        SEntityRequest request;

        for (unsigned int i = 0; i < amount; i++)
        {
            id = ++m_idCounter;
            m_entityRegistry.addEntity( id, signature );

            for( IComponentStorage *storage : vecStorages )
            {
                // create an instance of the component //
                storage->createComponent( id );
            }

            // request post tick handling of batches //
            request.id = id;
            request.type = EEntityRequestType::CREATE_ENTITY;
            // old signature is not needed, because hasn't had components before
            request.newSignature = signature;

            m_queuePostTickRequests.push( request );

            // actual entity and its components are created outright to allow component initialization on user's side
            // batches are processed only through request to maintain their coherence on per tick basis
            // so that no system misses out on all new components that get created on a single tick being available at the same time

            ids.push_back( id );
        }

        return ids;
    }

    std::vector< SComponentSet > CEntityManager::createEntitiesReturnSets( CEntitySignature signature, unsigned int amount )
    {
        std::vector< SComponentSet > vecCompSets;

        // validation stage
        if( signature.isEmpty() )
        {
            return vecCompSets;
        }

        // creation stage

        // get all needed component vectors
        std::vector< IComponentStorage *> vecStorages;
        for( const componenttindex_t& compTindex : signature.m_setComponentTindexes )
        {
            IComponentStorage *storage;
            storage = getComponentStorage( compTindex ); // let the exception propagate if happens
            storage->reserveMoreComponents( amount );
            vecStorages.push_back( storage ); 
        }

        entityid_t id;    
        IComponent *comp;
        SEntityRequest request;

        for (unsigned int i = 0; i < amount; i++)
        {
            SComponentSet compSet;

            id = ++m_idCounter;
            m_entityRegistry.addEntity( id, signature );
            compSet.componentOwnerID = id;
    
            for( IComponentStorage *storage : vecStorages )
            {
                // create an instance of the component //
                comp = storage->createComponent( id );
                compSet.addComponent( comp );
            }

            // request post tick handling of batches //
            request.id = id;
            request.type = EEntityRequestType::CREATE_ENTITY;
            // old signature is not needed, because hasn't had components before
            request.newSignature = signature;

            m_queuePostTickRequests.push( request );

            // actual entity and its components are created outright to allow component initialization on user's side
            // batches are processed only through request to maintain their coherence on per tick basis
            // so that no system misses out on all new components that get created on a single tick being available at the same time
            
            vecCompSets.push_back( compSet );
        }

        return vecCompSets;
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

        CEntitySignature signature;
        SEntityRequest request;


        // get the signature entity had before removing it
        signature = m_entityRegistry.getEntitySignature( id ); // hasEntity() ensures entity exists


        m_entityRegistry.removeEntity( id );


        // request post tick handling of CVWs and batches //
        request.id = id;
        request.type = EEntityRequestType::DESTROY_ENTITY;
        request.oldSignature = signature;
        // new signature is not needed as it will be empty anyways

        m_queuePostTickRequests.push( request );

        // only entity registry gets updated outright
        // actual components and batches are processed only through request to maintain their coherence on per tick basis
        // so that systems won't receive invalid components or batches in the middle of processing them
        // e.g. when component gets destroyed which invalidates its pointer, worse: its batch gets destroyed and it is invalid in the whole
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
        for( auto& [ tindex, storage ] : m_mapCompTypeToStorage )
        {
            storage->clearComponents();
        }

        m_vecCompBatches.clear();

        m_entityRegistry.removeAllEntities();
    }



    IComponent* CEntityManager::createComponent( componenttindex_t compTindex, entityid_t id ) 
    {
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

        IComponentStorage *storage;
        IComponent *uncastedComp;
        CEntitySignature oldSignature;
        CEntitySignature newSignature;
        SEntityRequest request;


        // compute signatures //
        oldSignature = m_entityRegistry.getEntitySignature( id ); // hasEntity() assures entity exists
        newSignature = oldSignature;
        newSignature.add( compTindex );


        // create an instance of the component //
        storage = getComponentStorage( compTindex ); // let the exception propagate if happens
        uncastedComp = storage->createComponent( id );


        // update entity registry - apply new signature to entity //
        m_entityRegistry.updateEntity( id, newSignature );


        // request post tick handling of batches //
        request.id = id;
        request.type = EEntityRequestType::CREATE_COMPONENT;
        request.oldSignature = oldSignature;
        request.newSignature = newSignature;

        m_queuePostTickRequests.push( request );

        // registry can be updated and component itself can be created outright
        // batches are processed only through request to maintain their coherence on per tick basis
        // so that systems won't receive invalid components or batches in the middle of processing them
        // e.g. when component gets created, all components belonging to entity should be moved to other batch
        // and this moving could lead to errors on current tick

        return uncastedComp;
    }

    bool CEntityManager::hasComponent( componenttindex_t compTindex, entityid_t id ) const
    {
        if( !hasEntity( id ) )
        {
            return false;
        }

        CEntitySignature signature;

        signature = m_entityRegistry.getEntitySignature( id ); // hasEntity() assures entity exists
        return signature.includes( compTindex );
    }

    IComponent* CEntityManager::getComponent( componenttindex_t compTindex, entityid_t id ) const
    {
        if( !hasComponent( compTindex, id ) )
        {
            return nullptr;
        }

        IComponentStorage *storage;
        IComponent *uncastedComp;

        storage = getComponentStorage( compTindex );
        uncastedComp = storage->getComponent( id );

        return uncastedComp;
    }

    void CEntityManager::destroyComponent( componenttindex_t compTindex, entityid_t id ) 
    {
        if( !hasComponent( compTindex, id ) )
        {
            LOG_CHANNEL( "ENTITY_MANAGER", "Entity " << id << " doesn't have component " << compTindex.name() );
            return;
        }

        CEntitySignature oldSignature;
        CEntitySignature newSignature;
        SEntityRequest request;


        // compute signatures //
        oldSignature = m_entityRegistry.getEntitySignature( id ); // hasComponent() assures entity exists
        newSignature = oldSignature;
        newSignature.remove( compTindex );


        // update registry //
        m_entityRegistry.updateEntity( id, newSignature );


        // request post tick handling of CVWs batches //
        request.id = id;
        request.type = EEntityRequestType::DESTROY_COMPONENT;
        request.oldSignature = oldSignature;
        request.newSignature = newSignature;

        m_queuePostTickRequests.push( request );

        // registry can be updated outright
        // actual component and batches are processed only through request to maintain their coherence on per tick basis
        // so that systems won't receive invalid components or batches in the middle of processing them
        // e.g. when component gets destroyed, all components belonging to entity should be moved to other batch
        // and this moving could lead to errors on current tick
    }

    SComponentSet CEntityManager::getComponentSet( entityid_t id ) 
    {
        SComponentSet compSet;

        if( !hasEntity( id ) )
        {
            // return empty set with ENTITY_ID_INVALID
            return compSet;
        }
        
        compSet.componentOwnerID = id;

        CEntitySignature sign = m_entityRegistry.getEntitySignature( id );
        if( sign.isEmpty() )
        {
            // return empty set
            return compSet;
        }

        compSet = buildComponentSetForEntity( id, sign );

        return compSet;
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



    bool CEntityManager::processEntityRequests() 
    {
        if( m_queuePostTickRequests.empty() )
        {
            return false;
        }

        while( !m_queuePostTickRequests.empty() )
        {
            SEntityRequest& request = m_queuePostTickRequests.front();

            switch( request.type )
            {
                case EEntityRequestType::CREATE_ENTITY:
                    processPostTickCreateEntityRequest( request );
                    break;

                case EEntityRequestType::DESTROY_ENTITY:
                    processPostTickDestroyEntityRequest( request );
                    break;

                case EEntityRequestType::CREATE_COMPONENT:
                    processPostTickCreateComponentRequest( request );
                    break;

                case EEntityRequestType::DESTROY_COMPONENT:
                    processPostTickDestroyComponentRequest( request );
                    break;
            }

            m_queuePostTickRequests.pop();
        }

        return true;
    }

    // ========================= PRIVATE ========================= //

    IComponentStorage* CEntityManager::getComponentStorage( componenttindex_t compTypeTindex ) const
    {
        auto it = m_mapCompTypeToStorage.find( compTypeTindex );
        // if storage exists for that type
        if( it != m_mapCompTypeToStorage.end() )
        {
            return it->second;
        }
        else
        {
            throw ChestnutException( "Component type has not been set up in the entity manager: " + std::string( compTypeTindex.name() ) );
        }
    }



    bool CEntityManager::existsBatchWithSignature( CEntitySignature signature ) const
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

    CComponentBatch *CEntityManager::getBatchWithSignature( CEntitySignature signature ) 
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

    void CEntityManager::createBatchWithSignature( CEntitySignature signature ) 
    {
        m_vecCompBatches.push_back( CComponentBatch( signature ) );
    }

    void CEntityManager::destroyBatchWithSignature( CEntitySignature signature ) 
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



    SComponentSet CEntityManager::buildComponentSetForEntity( entityid_t id, CEntitySignature signature ) 
    {
        SComponentSet compSet;
        IComponentStorage *storage;
        IComponent *comp;

        compSet.componentOwnerID = id;

        for( const std::type_index& tindex : signature.m_setComponentTindexes )
        {
            storage = getComponentStorage( tindex );

            comp = storage->getComponent( id );
            compSet.addComponent( comp );
        }

        return compSet;
    }

    bool CEntityManager::moveEntityAccrossBatches( entityid_t id, CEntitySignature oldSignature, CEntitySignature newSignature ) 
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



    void CEntityManager::processPostTickCreateEntityRequest( const SEntityRequest& request ) 
    {
        // empty old signature means it won't attempt to remove components from old one, because it hasn't been assigned to one yet
        moveEntityAccrossBatches( request.id, CEntitySignature(), request.newSignature );
    }

    void CEntityManager::processPostTickDestroyEntityRequest( const SEntityRequest& request ) 
    {
        IComponentStorage *storage;

        // remove actual components belonging to entity
        for( const std::type_index& tindex : request.oldSignature.m_setComponentTindexes )
        {
            storage = getComponentStorage( tindex );
            storage->eraseComponent( request.id );
        }

        // empty new signature means it will get removed from new one and not assigned to any new
        moveEntityAccrossBatches( request.id, request.oldSignature, CEntitySignature() );
    }

    void CEntityManager::processPostTickCreateComponentRequest( const SEntityRequest& request ) 
    {
        moveEntityAccrossBatches( request.id, request.oldSignature, request.newSignature );
    }

    void CEntityManager::processPostTickDestroyComponentRequest( const SEntityRequest& request ) 
    {
        CEntitySignature signDiff = request.oldSignature - request.newSignature;
        componenttindex_t destroyedCompTindex = *( signDiff.m_setComponentTindexes.begin() );
        IComponentStorage *storage = getComponentStorage( destroyedCompTindex );

        storage->eraseComponent( request.id );

        moveEntityAccrossBatches( request.id, request.oldSignature, request.newSignature );
    }

} // namespace chestnut
