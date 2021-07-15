#ifndef __CHESTNUT_ENTITY_MANAGER_H__
#define __CHESTNUT_ENTITY_MANAGER_H__

#include "entity_signature.hpp"
#include "component_set.hpp"
#include "entity_registry.hpp"
#include "component_batch.hpp"
#include "component_storage.hpp"
#include "entity_request.hpp"

#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace chestnut
{
    class CEntityManager
    {
    private:
        // A counter used to distribute IDs to entities
        entityid_t m_idCounter;

        // A bookkeeping object used to keep track of created entities and their signatures
        CEntityRegistry m_entityRegistry;

        // A map pointing to direct component storages
        std::unordered_map< componenttindex_t, IComponentStorage * > m_mapCompTypeToStorage;

        // A vector of component batches, which reference components from the component map
        std::vector< CComponentBatch > m_vecCompBatches;

        // a queue of requests for adding/destroying components or whole entities
        std::queue< SEntityRequest > m_queuePostTickRequests;


    public:
        CEntityManager();

        CEntityManager( const CEntityManager& ) = delete; // we don't allow copying components

        ~CEntityManager();


        template< typename T >
        void setupComponentType( size_t segmentSize );


        entityid_t createEntity();

        std::vector< entityid_t > createEntities( unsigned int amount );

        // Throws an exception if any of component types in signature have not been set up for the manager
        entityid_t createEntity( CEntitySignature signature );

        // Throws an exception if any of component types in signature have not been set up for the manager
        std::vector< entityid_t > createEntities( CEntitySignature signature, unsigned int amount );
        // Throws an exception if any of component types in signature have not been set up for the manager
        std::vector< SComponentSet > createEntitiesReturnSets( CEntitySignature signature, unsigned int amount );

        bool hasEntity( entityid_t id ) const;

        void destroyEntity( entityid_t id );

        void destroyEntities( std::vector< entityid_t > ids );

        void destroyAllEntities();

        //TODO hide functions with tindices as arguments

        // Throws an exception if component type has not been set up for the manager
        IComponent *createComponent( componenttindex_t compTindex, entityid_t id );

        bool hasComponent( componenttindex_t compTindex, entityid_t id ) const;

        // Throws an exception if component type has not been set up for the manager
        IComponent *getComponent( componenttindex_t compTindex, entityid_t id ) const;

        void destroyComponent( componenttindex_t compTindex, entityid_t id );

        SComponentSet getComponentSet( entityid_t id );


        // Throws an exception if component type has not been set up for the manager
        // Returns null on error
        template< typename T >
        T *createComponent( entityid_t id );

        // Throws an exception if component type has not been set up for the manager
        template< typename T >
        bool hasComponent( entityid_t id ) const;

        // Throws an exception if component type has not been set up for the manager
        // Returns null on error
        template< typename T >
        T *getComponent( entityid_t id ) const;

        // Throws an exception if component type has not been set up for the manager
        template< typename T >
        void destroyComponent( entityid_t id );


        std::vector< CComponentBatch * > getComponentBatches();

        // Returns true if had any requests to process
        bool processEntityRequests();


    private:
        // Throws exception if doesn't find the storage (manager was not prepared for specified type)
        IComponentStorage *getComponentStorage( componenttindex_t compTindex ) const;


        bool existsBatchWithSignature( CEntitySignature signature ) const;

        // Returns null if doesn't find one
        CComponentBatch *getBatchWithSignature( CEntitySignature signature );

        void createBatchWithSignature( CEntitySignature signature );

        void destroyBatchWithSignature( CEntitySignature signature );


        SComponentSet buildComponentSetForEntity( entityid_t id, CEntitySignature signature );

        bool moveEntityAccrossBatches( entityid_t id, CEntitySignature oldSignature, CEntitySignature newSignature );


        void processPostTickCreateComponentRequest( const SEntityRequest& request );

        void processPostTickDestroyComponentRequest( const SEntityRequest& request );

        void processPostTickCreateEntityRequest( const SEntityRequest& request );

        void processPostTickDestroyEntityRequest( const SEntityRequest& request );
    };
    
} // namespace chestnut


#include "entity_manager.tpp"


#endif // __CHESTNUT_ENTITY_MANAGER_H__