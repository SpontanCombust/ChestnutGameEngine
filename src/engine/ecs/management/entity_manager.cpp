#include "entity_manager.hpp"

namespace chestnut
{    
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



    bool CEntityManager::existsBatchWithSignature( SComponentSetSignature signature ) 
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

    IComponentVectorWrapper* CEntityManager::getComponentVectorWrapperUnsafe( std::type_index compTypeTindex ) 
    {
        IComponentVectorWrapper *wrapper;

        wrapper = nullptr;

        auto it = m_mapComponentVecWrappers.find( compTypeTindex );
        // vector wrapper doesn't yet exist for this type
        if( it != m_mapComponentVecWrappers.end() )
        {
            wrapper = m_mapComponentVecWrappers[ compTypeTindex ];
        }

        return wrapper;
    }

    SComponentSet CEntityManager::buildComponentSetForEntity( entityid_t id, SComponentSetSignature signature ) 
    {
        SComponentSet compSet;
        IComponentVectorWrapper *wrapper;
        IComponent *comp;

        compSet.componentOwnerID = id;

        for( const std::type_index& tindex : signature.componentTindexes )
        {
            wrapper = getComponentVectorWrapperUnsafe( tindex );
            comp = wrapper->at( id );
            compSet.addComponent( comp );
        }

        return compSet;
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

        try
        {
            signature = m_entityRegistry.getEntitySignature( id );
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
                vecWrapper = getComponentVectorWrapperUnsafe( tindex );
                vecWrapper->erase( id );
            }

            // remove entity from registry
            m_entityRegistry.removeEntity( id );
        }
        catch( const std::exception& e )
        {
            std::cerr << e.what() << '\n';
        }
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



    std::vector< CComponentBatch * > CEntityManager::getComponentBatches() 
    {
        std::vector< CComponentBatch * > vec;

        for( CComponentBatch& batch : m_vecCompBatches )
        {
            vec.push_back( &batch );
        }

        return vec;
    }

} // namespace chestnut
