#ifndef __CHESTNUT_ENTITY_MANAGER_H__
#define __CHESTNUT_ENTITY_MANAGER_H__

#include "component_set_signature.hpp"
#include "component_set.hpp"
#include "entity_registry.hpp"
#include "component_batch.hpp"
#include "component_vector_wrapper.hpp"

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
        std::unordered_map< std::type_index, IComponentVectorWrapper * > m_mapComponentVecWrappers;
        // A vector of component batches, which reference components from the component map
        std::vector< CComponentBatch > m_vecCompBatches;

    public:
        CEntityManager();

        CEntityManager( const CEntityManager& ) = delete; // we don't allow copying components

        ~CEntityManager();


        entityid_t createEntity();

        std::vector< entityid_t > createEntities( int amount );

        bool hasEntity( entityid_t id ) const;

        void destroyEntity( entityid_t id );

        void destroyEntities( std::vector< entityid_t > ids );

        void destroyAllEntities();


        // Returns null on error
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


    private:
        bool existsBatchWithSignature( SComponentSetSignature signature );

        // Returns null if doesn't find one
        CComponentBatch *getBatchWithSignature( SComponentSetSignature signature );

        void createBatchWithSignature( SComponentSetSignature signature );

        void destroyBatchWithSignature( SComponentSetSignature signature );


        // Ensures existence of the vector wrapper in the map by creating one if necessary
        template< typename T >
        IComponentVectorWrapper *getComponentVectorWrapper();

        // Doesn't ensure existence of the vector wrapper in the map, returns null on failure
        IComponentVectorWrapper *getComponentVectorWrapperUnsafe( std::type_index compTypeTindex );

        // Throws exception on error. Fetches components from component vector wrappers and packs their pointers into a component set
        SComponentSet buildComponentSetForEntity( entityid_t id, SComponentSetSignature signature );
    };
    
} // namespace chestnut


#include "entity_manager.tpp"


#endif // __CHESTNUT_ENTITY_MANAGER_H__