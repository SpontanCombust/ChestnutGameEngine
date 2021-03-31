#include "component_batch.hpp"

#include "engine/debug/debug.hpp"

#include <algorithm>

namespace chestnut
{
    CComponentBatch::CComponentBatch( const SComponentBundleSignature& signature ) 
    {
        m_signature = signature;
    }

    CComponentBatch::~CComponentBatch() 
    {
        m_entityIDs.clear();
        m_mapTindexToCompVec.clear();
    }

    void CComponentBatch::setSignature( const SComponentBundleSignature& signature ) 
    {
        m_signature = signature;

        // remove components that don't belong to new signature
        for( const auto& [ tindex, vec ] : m_mapTindexToCompVec )
        {
            if( !signature.includes( tindex ) )
            {
                m_mapTindexToCompVec.erase( tindex );
            }
        }
    }

    const SComponentBundleSignature& CComponentBatch::getSignature() const
    {
        return m_signature;
    }

    const std::vector< entityid_t >& CComponentBatch::getEntities() const
    {
        return m_entityIDs;
    }

    void CComponentBatch::submitBundle( const SComponentBundle& bundle ) 
    {
        // check if the bundle is even for this batch
        if( bundle.getSignature() == m_signature )
        {
            // check if entity isn't already in the batch
            auto foundEntity = std::find( m_entityIDs.begin(), m_entityIDs.end(), bundle.componentOwnerID );
            if( foundEntity == m_entityIDs.end() )
            {
                m_entityIDs.push_back( bundle.componentOwnerID );

                // copy component pointers from bundle to local vectors
                for( const auto& [ tindex, comp ] : bundle.mapTindexToComponent )
                {
                    m_mapTindexToCompVec[ tindex ].push_back( comp );
                }   
            }
        }
        else
        {
            LOG_CHANNEL( "COMPONENT_BATCH", "Tried to submit bundle with incompatible signature!" );
            LOG_CHANNEL( "COMPONENT_BATCH", "This batch's signature is: " + m_signature.toString() );
            LOG_CHANNEL( "COMPONENT_BATCH", "Bundle's signature is: " + bundle.getSignature().toString() );
        }
    }

    void CComponentBatch::removeEntityAndComponents( entityid_t id ) 
    {
        if( m_entityIDs.size() > 0 )
        {
            // check if entity is in batch
            size_t i;
            for (i = 0; i < m_entityIDs.size(); i++)
            {
                if( m_entityIDs[i] == id )
                {
                    break;
                }
            }
            
            // if index is lesser than size, the entity exists in the batch
            if( i < m_entityIDs.size() )
            {
                m_entityIDs.erase( m_entityIDs.begin() + i );

                // remove components belonging to entity
                for( auto& [ tindex, compVec ] : m_mapTindexToCompVec )
                {
                    // by using only bundles to add components we can be sure the same index in all vectors (entity id and components)
                    // is used for the same entity
                    // components are always pushed back, never sorted and always deleted in bulk
                    // (both entity ID and all components belonging to that entity get removed),
                    // so their order stays the same all the time
                    compVec.erase( compVec.begin() + i );
                }
            }
        }
    }

    void CComponentBatch::removeAllEntitiesAndComponents() 
    {
        m_entityIDs.clear();
        m_mapTindexToCompVec.clear();
    }

} // namespace chestnut
