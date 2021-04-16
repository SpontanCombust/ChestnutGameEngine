#ifndef __CHESTNUT_ENTITY_MANAGER_H__
#define __CHESTNUT_ENTITY_MANAGER_H__

#include "component_set_signature.hpp"
#include "component_set.hpp"
#include "entity_registry.hpp"
#include "component_batch.hpp"
#include "component_vector_wrapper.hpp"
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

        // A map pointing to direct component storages (vector wrappers)
        std::unordered_map< componenttindex_t, IComponentVectorWrapper * > m_mapComponentVecWrappers;

        // A vector of component batches, which reference components from the component map
        std::vector< CComponentBatch > m_vecCompBatches;

        // a queue of requests for adding/destroying components or whole entities
        std::queue< SEntityRequest > m_queuePostTickRequests;


    public:
        CEntityManager();

        CEntityManager( const CEntityManager& ) = delete; // we don't allow copying components

        ~CEntityManager();


        template< typename T >
        CEntityManager& prepareForComponentType();


        entityid_t createEntity();

        std::vector< entityid_t > createEntities( int amount );

        // Returns ENTITY_ID_INVALID if manager was not prepared for component type
        entityid_t createEntity( SComponentSetSignature signature );

        // Returns empty vector if manager was not prepared for component type
        std::vector< entityid_t > createEntities( SComponentSetSignature signature, int amount );

        bool hasEntity( entityid_t id ) const;

        void destroyEntity( entityid_t id );

        void destroyEntities( std::vector< entityid_t > ids );

        void destroyAllEntities();


        // Returns null if manager was not prepared for component type
        IComponent *createComponent( componenttindex_t compTindex, entityid_t id );

        bool hasComponent( componenttindex_t compTindex, entityid_t id ) const;

        // Returns null if manager was not prepared for component type
        IComponent *getComponent( componenttindex_t compTindex, entityid_t id );

        void destroyComponent( componenttindex_t compTindex, entityid_t id );


        // Returns null on error. Additionally prepares manager for given component type.
        template< typename T >
        T *createComponent( entityid_t id );

        template< typename T >
        bool hasComponent( entityid_t id ) const;

        // Returns null on error
        template< typename T >
        T *getComponent( entityid_t id );

        template< typename T >
        void destroyComponent( entityid_t id );


        std::vector< CComponentBatch * > getComponentBatches();


        void processEntityRequests();


    private:
        bool isPreparedForComponentType( componenttindex_t compTindex ) const;


        // Returns null if doesn't find one
        IComponentVectorWrapper *getComponentVectorWrapper( componenttindex_t compTindex ) const;


        bool existsBatchWithSignature( SComponentSetSignature signature ) const;

        // Returns null if doesn't find one
        CComponentBatch *getBatchWithSignature( SComponentSetSignature signature );

        void createBatchWithSignature( SComponentSetSignature signature );

        void destroyBatchWithSignature( SComponentSetSignature signature );


        SComponentSet buildComponentSetForEntity( entityid_t id, SComponentSetSignature signature );

        bool moveEntityAccrossBatches( entityid_t id, SComponentSetSignature oldSignature, SComponentSetSignature newSignature );


        void processPostTickCreateComponentRequest( const SEntityRequest& request );

        void processPostTickDestroyComponentRequest( const SEntityRequest& request );

        void processPostTickCreateEntityRequest( const SEntityRequest& request );

        void processPostTickDestroyEntityRequest( const SEntityRequest& request );
    };
    
} // namespace chestnut


#include "entity_manager.tpp"


#endif // __CHESTNUT_ENTITY_MANAGER_H__